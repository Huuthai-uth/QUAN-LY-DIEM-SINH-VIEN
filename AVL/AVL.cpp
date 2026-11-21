#include "AVL.h"
#include <sstream>

using namespace std;

// ===================== NODE & CAY =====================
NodeAVL::NodeAVL(const SinhVien& sv)
{
    data = sv;
    left = NULL;
    right = NULL;
    height = 1;
}

CayAVL::CayAVL()
{
    root = NULL;
    soLuong = 0;
}

void KhoiTaoCay(CayAVL& cay)
{
    cay.root = NULL;
    cay.soLuong = 0;
}

static void GiaiPhongNode(NodeAVL* node)
{
    if (node == NULL)
        return;

    GiaiPhongNode(node->left);
    GiaiPhongNode(node->right);
    delete node;
}

void GiaiPhongCay(CayAVL& cay)
{
    GiaiPhongNode(cay.root);
    cay.root = NULL;
    cay.soLuong = 0;
}

// ===================== CHIEU CAO & HE SO CAN BANG =====================
int ChieuCao(const NodeAVL* node)
{
    return (node == NULL) ? 0 : node->height;
}

void CapNhatChieuCao(NodeAVL* node)
{
    if (node == NULL)
        return;

    int cl = ChieuCao(node->left);
    int cr = ChieuCao(node->right);
    node->height = 1 + (cl > cr ? cl : cr);
}

int HeSoCanBang(const NodeAVL* node)
{
    if (node == NULL)
        return 0;

    return ChieuCao(node->left) - ChieuCao(node->right);
}

// ===================== XOAY =====================

NodeAVL* XoayPhai(NodeAVL* y)
{
    NodeAVL* x = y->left;
    NodeAVL* B = x->right;

    x->right = y;
    y->left = B;

    CapNhatChieuCao(y);
    CapNhatChieuCao(x);

    return x;
}

NodeAVL* XoayTrai(NodeAVL* x)
{
    NodeAVL* y = x->right;
    NodeAVL* B = y->left;

    y->left = x;
    x->right = B;

    CapNhatChieuCao(x);
    CapNhatChieuCao(y);

    return y;
}

// ===================== CAN BANG: LL, RR, LR, RL =====================
NodeAVL* CanBang(NodeAVL* node)
{
    if (node == NULL)
        return NULL;

    CapNhatChieuCao(node);
    int hs = HeSoCanBang(node);

    // Lech trai
    if (hs > 1)
    {
        // LR: con trai lech phai -> xoay trai con trai truoc
        if (HeSoCanBang(node->left) < 0)
            node->left = XoayTrai(node->left);

        // LL (hoac phan sau cua LR): xoay phai tai node
        return XoayPhai(node);
    }

    // Lech phai
    if (hs < -1)
    {
        // RL: con phai lech trai -> xoay phai con phai truoc
        if (HeSoCanBang(node->right) > 0)
            node->right = XoayPhai(node->right);

        // RR (hoac phan sau cua RL): xoay trai tai node
        return XoayTrai(node);
    }

    return node;    // da can bang
}

// ===================== THEM =====================
static NodeAVL* ThemNode(NodeAVL* node, const SinhVien& sv, bool& thanhCong)
{
    if (node == NULL)
    {
        thanhCong = true;
        return new NodeAVL(sv);
    }

    if (sv.MSSV < node->data.MSSV)
        node->left = ThemNode(node->left, sv, thanhCong);
    else if (sv.MSSV > node->data.MSSV)
        node->right = ThemNode(node->right, sv, thanhCong);
    else
    {
        thanhCong = false;      // trung MSSV
        return node;
    }

    return CanBang(node);
}

bool ThemSinhVien(CayAVL& cay, const SinhVien& sv)
{
    if (!KiemTraSinhVienHopLe(sv))
        return false;

    bool thanhCong = false;
    cay.root = ThemNode(cay.root, sv, thanhCong);

    if (thanhCong)
        cay.soLuong++;

    return thanhCong;
}

// ===================== XOA =====================
static NodeAVL* TimNodeNhoNhat(NodeAVL* node)
{
    while (node->left != NULL)
        node = node->left;

    return node;
}

static NodeAVL* XoaNode(NodeAVL* node, const string& mssv, bool& thanhCong)
{
    if (node == NULL)
    {
        thanhCong = false;
        return NULL;
    }

    if (mssv < node->data.MSSV)
    {
        node->left = XoaNode(node->left, mssv, thanhCong);
    }
    else if (mssv > node->data.MSSV)
    {
        node->right = XoaNode(node->right, mssv, thanhCong);
    }
    else
    {
        thanhCong = true;

        // Truong hop 0 hoac 1 con
        if (node->left == NULL || node->right == NULL)
        {
            NodeAVL* con = (node->left != NULL) ? node->left : node->right;
            delete node;
            return con;
        }

        NodeAVL* ke = TimNodeNhoNhat(node->right);
        string mssvKe = ke->data.MSSV;

        node->data = ke->data;

        bool tam = false;
        node->right = XoaNode(node->right, mssvKe, tam);
    }

    return CanBang(node);
}

bool XoaSinhVien(CayAVL& cay, const string& mssv)
{
    bool thanhCong = false;
    cay.root = XoaNode(cay.root, mssv, thanhCong);

    if (thanhCong)
        cay.soLuong--;

    return thanhCong;
}

// ===================== TIM =====================
NodeAVL* TimSinhVien(CayAVL& cay, const string& mssv)
{
    NodeAVL* p = cay.root;

    while (p != NULL)
    {
        if (mssv == p->data.MSSV)
            return p;

        p = (mssv < p->data.MSSV) ? p->left : p->right;
    }

    return NULL;
}

const NodeAVL* TimSinhVien(const CayAVL& cay, const string& mssv)
{
    const NodeAVL* p = cay.root;

    while (p != NULL)
    {
        if (mssv == p->data.MSSV)
            return p;

        p = (mssv < p->data.MSSV) ? p->left : p->right;
    }

    return NULL;
}

// ===================== DUYET =====================
static void InThongTinNode(const NodeAVL* node)
{
    cout << node->data.MSSV << " - " << node->data.HoTen
         << "  [h=" << node->height
         << ", hs=" << HeSoCanBang(node) << "]\n";
}

static void LNR(const NodeAVL* node)
{
    if (node == NULL) return;
    LNR(node->left);
    InThongTinNode(node);
    LNR(node->right);
}

static void NLR(const NodeAVL* node)
{
    if (node == NULL) return;
    InThongTinNode(node);
    NLR(node->left);
    NLR(node->right);
}

static void LRN(const NodeAVL* node)
{
    if (node == NULL) return;
    LRN(node->left);
    LRN(node->right);
    InThongTinNode(node);
}

void DuyetLNR(const CayAVL& cay)
{
    if (cay.root == NULL) { cout << "Cay rong.\n"; return; }
    cout << "\n===== DUYET LNR (tang dan theo MSSV) =====\n";
    LNR(cay.root);
}

void DuyetNLR(const CayAVL& cay)
{
    if (cay.root == NULL) { cout << "Cay rong.\n"; return; }
    cout << "\n===== DUYET NLR =====\n";
    NLR(cay.root);
}

void DuyetLRN(const CayAVL& cay)
{
    if (cay.root == NULL) { cout << "Cay rong.\n"; return; }
    cout << "\n===== DUYET LRN =====\n";
    LRN(cay.root);
}

static void InCay(const NodeAVL* node, int mucLui)
{
    if (node == NULL)
        return;

    InCay(node->right, mucLui + 6);

    for (int i = 0; i < mucLui; i++)
        cout << ' ';
    cout << node->data.MSSV << " (h=" << node->height << ")\n";

    InCay(node->left, mucLui + 6);
}

void InCayDangCay(const CayAVL& cay)
{
    if (cay.root == NULL) { cout << "Cay rong.\n"; return; }
    cout << "\n===== HINH DANG CAY (xoay ngang: phai o tren, trai o duoi) =====\n";
    InCay(cay.root, 0);
}

// ===================== KIEM TRA TINH HOP LE CUA AVL =====================
static bool KiemTraNode(const NodeAVL* node, const string* thap, const string* cao, int& chieuCao)
{
    if (node == NULL)
    {
        chieuCao = 0;
        return true;
    }

    if (thap != NULL && !(node->data.MSSV > *thap))
        return false;
    if (cao != NULL && !(node->data.MSSV < *cao))
        return false;

    int hl = 0, hr = 0;

    if (!KiemTraNode(node->left, thap, &node->data.MSSV, hl))
        return false;
    if (!KiemTraNode(node->right, &node->data.MSSV, cao, hr))
        return false;

    int diff = hl - hr;
    if (diff < -1 || diff > 1)
        return false;

    chieuCao = 1 + (hl > hr ? hl : hr);

    return node->height == chieuCao;
}

static int DemNode(const NodeAVL* node)
{
    return (node == NULL) ? 0 : 1 + DemNode(node->left) + DemNode(node->right);
}

bool KiemTraCayAVL(const CayAVL& cay)
{
    int h = 0;

    if (!KiemTraNode(cay.root, NULL, NULL, h))
        return false;

    return DemNode(cay.root) == cay.soLuong;
}

// ===================== KIEM THU =====================
static SinhVien TaoSVTest(int so)
{
    ostringstream oss;
    oss << so;

    SinhVien sv;
    sv.MSSV = oss.str();
    while (sv.MSSV.length() < 5)
        sv.MSSV = "0" + sv.MSSV;

    sv.HoTen = "Sinh Vien " + oss.str();
    sv.Lop = "TEST01";
    sv.NgaySinh = "15/03/2005";
    return sv;
}

static string KhoaTest(int so)
{
    return TaoSVTest(so).MSSV;
}

static bool Kiem(bool dieuKien, const string& tenTest)
{
    cout << (dieuKien ? "[PASS] " : "[FAIL] ") << tenTest << '\n';
    return dieuKien;
}

static bool TestXoay(const string& ten, const int khoa[], int n, int gocMongDoi)
{
    CayAVL cay;
    for (int i = 0; i < n; i++)
        ThemSinhVien(cay, TaoSVTest(khoa[i]));

    bool ok = (cay.root != NULL)
           && cay.root->data.MSSV == KhoaTest(gocMongDoi)
           && KiemTraCayAVL(cay);

    GiaiPhongCay(cay);
    return Kiem(ok, ten);
}

bool KiemThuCanBang()
{
    cout << "\n========== KIEM THU CAY AVL ==========\n";
    bool tatCa = true;
    int ll[] = { 30, 20, 10 };
    int rr[] = { 10, 20, 30 };
    int lr[] = { 30, 10, 20 };
    int rl[] = { 10, 30, 20 };

    tatCa &= TestXoay("LL (30,20,10) -> goc 20", ll, 3, 20);
    tatCa &= TestXoay("RR (10,20,30) -> goc 20", rr, 3, 20);
    tatCa &= TestXoay("LR (30,10,20) -> goc 20", lr, 3, 20);
    tatCa &= TestXoay("RL (10,30,20) -> goc 20", rl, 3, 20);
    {
        CayAVL cay;
        ThemSinhVien(cay, TaoSVTest(10));
        bool trung = ThemSinhVien(cay, TaoSVTest(10));
        tatCa &= Kiem(!trung && cay.soLuong == 1, "Tu choi MSSV trung");
        GiaiPhongCay(cay);
    }

    {
        const int N = 1000;
        CayAVL cay;
        bool ok = true;

        for (int i = 1; i <= N; i++)
        {
            ThemSinhVien(cay, TaoSVTest(i));
            if (!KiemTraCayAVL(cay))
                ok = false;
        }

       
        int h = ChieuCao(cay.root);
        ostringstream moTa;
        moTa << "Chen tang dan 1000 SV van can bang (chieu cao = " << h << ")";
        tatCa &= Kiem(ok && cay.soLuong == N && h <= 14, moTa.str());

        bool timOK = (TimSinhVien(cay, KhoaTest(500)) != NULL)
                  && (TimSinhVien(cay, KhoaTest(1)) != NULL)
                  && (TimSinhVien(cay, KhoaTest(1000)) != NULL)
                  && (TimSinhVien(cay, KhoaTest(5000)) == NULL);
        tatCa &= Kiem(timOK, "Tim kiem (co / khong co)");

        bool xoaOK = true;
        int daXoa = 0;
        for (int i = 2; i <= N; i += 2)
        {
            if (!XoaSinhVien(cay, KhoaTest(i)))
                xoaOK = false;
            else
                daXoa++;

            if (!KiemTraCayAVL(cay))
                xoaOK = false;
        }
        tatCa &= Kiem(xoaOK && cay.soLuong == N - daXoa, "Xoa 500 SV, cay luon can bang");

        tatCa &= Kiem(!XoaSinhVien(cay, KhoaTest(5000)), "Xoa MSSV khong ton tai tra ve false");

        bool rongOK = true;
        for (int i = 1; i <= N; i += 2)
        {
            if (!XoaSinhVien(cay, KhoaTest(i)) || !KiemTraCayAVL(cay))
                rongOK = false;
        }
        tatCa &= Kiem(rongOK && cay.root == NULL && cay.soLuong == 0, "Xoa het -> cay rong");

        GiaiPhongCay(cay);
    }

    {
        int khoa[] = { 50, 30, 70, 20, 40, 60, 80, 35, 45 };
        CayAVL cay;
        for (int i = 0; i < 9; i++)
            ThemSinhVien(cay, TaoSVTest(khoa[i]));

        bool ok = XoaSinhVien(cay, KhoaTest(30))
               && TimSinhVien(cay, KhoaTest(30)) == NULL
               && TimSinhVien(cay, KhoaTest(35)) != NULL
               && KiemTraCayAVL(cay);
        tatCa &= Kiem(ok, "Xoa node co 2 con");

        ok = XoaSinhVien(cay, KhoaTest(50)) && KiemTraCayAVL(cay);
        tatCa &= Kiem(ok, "Xoa node goc");

        GiaiPhongCay(cay);
    }
    cout << (tatCa ? "\n=> TAT CA TEST DEU PASS.\n" : "\n=> CO TEST BI FAIL!\n");
    return tatCa;
}
