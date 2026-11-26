#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <chrono>
#include <random>
#include <iostream>
#include <cstdio>

using namespace std;

namespace {
    string loaiBoKyTuXuongDong(const string& s) {
        string res = s;
        while (!res.empty() && (res.back() == '\r' || res.back() == '\n')) {
            res.pop_back();
        }
        return res;
    }

    string catKhoangTrangHaiDau(const string& s) {
        size_t start = 0;
        while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
            ++start;
        }
        size_t end = s.size();
        while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
            --end;
        }
        return s.substr(start, end - start);
    }

    // Tach chuoi theo dau '|' vao mang dong string*
    string* tachTheoDauGachDung(const string& line, int& soPhanTu) {
        soPhanTu = 0;
        if (line.empty()) {
            return nullptr;
        }

        int dem = 1;
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '|') {
                ++dem;
            }
        }

        string* parts = new string[dem];
        int idx = 0;
        size_t start = 0;
        for (size_t i = 0; i <= line.size(); ++i) {
            if (i == line.size() || line[i] == '|') {
                string item = line.substr(start, i - start);
                parts[idx++] = loaiBoKyTuXuongDong(item);
                start = i + 1;
            }
        }

        soPhanTu = idx;
        return parts;
    }

    void giaiPhongMangString(string*& arr) {
        delete[] arr;
        arr = nullptr;
    }

    bool parseSoNguyenAnToan(const string& text, int& giaTri) {
        string clean = catKhoangTrangHaiDau(text);
        if (clean.empty()) {
            return false;
        }
        size_t i = 0;
        if (clean[0] == '+' || clean[0] == '-') {
            i = 1;
        }
        if (i >= clean.size()) {
            return false;
        }
        for (; i < clean.size(); ++i) {
            if (!isdigit(static_cast<unsigned char>(clean[i]))) {
                return false;
            }
        }
        try {
            size_t idx = 0;
            long long val = stoll(clean, &idx, 10);
            if (idx != clean.size() || val < -2147483648LL || val > 2147483647LL) {
                return false;
            }
            giaTri = static_cast<int>(val);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool parseSoThucFloatAnToan(const string& text, float& giaTri) {
        string clean = catKhoangTrangHaiDau(text);
        if (clean.empty()) {
            return false;
        }
        try {
            size_t idx = 0;
            float val = stof(clean, &idx);
            if (idx != clean.size() || !kiemTraDiem(val)) {
                return false;
            }
            giaTri = val;
            return true;
        } catch (...) {
            return false;
        }
    }

    void ghiDeQuyAVL(AVLNode* node, ofstream& outSV, ofstream& outHP,
                     int& tongSV, int& tongHP) {
        if (node == nullptr) {
            return;
        }

        ghiDeQuyAVL(node->left, outSV, outHP, tongSV, tongHP);

        const SinhVien& sv = node->data;
        outSV << sv.mssv << '|'
              << sv.hoTen << '|'
              << sv.lop << '|'
              << sv.ngaySinh << '\n';
        ++tongSV;

        const HocPhan* cur = sv.dsHocPhan;
        while (cur != nullptr) {
            outHP << sv.mssv << '|'
                  << cur->maHP << '|'
                  << cur->tenHP << '|'
                  << cur->soTinChi << '|'
                  << fixed << setprecision(2) << cur->diemHe10 << '\n';
            ++tongHP;
            cur = cur->next;
        }

        ghiDeQuyAVL(node->right, outSV, outHP, tongSV, tongHP);
    }

    string taoMaSVChuan(int chiSo) {
        char boDem[24];
        snprintf(boDem, sizeof(boDem), "SV%06d", chiSo);
        return string(boDem);
    }

    void xaoTronMangSinhVien(SinhVien* arr, int n, mt19937& rng) {
        for (int i = n - 1; i > 0; --i) {
            uniform_int_distribution<int> dist(0, i);
            int j = dist(rng);
            if (i != j) {
                SinhVien temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    void giaiPhongMangSinhVien(SinhVien*& arr, int n) {
        if (arr == nullptr) {
            return;
        }
        for (int i = 0; i < n; ++i) {
            giaiPhongSinhVien(arr[i]);
        }
        delete[] arr;
        arr = nullptr;
    }
}

KetQuaFile docVaNapSinhVienAVL(const string& duongDanFile, AVLNode*& rootAVL) {
    KetQuaFile kq;
    ifstream ifs(duongDanFile);
    if (!ifs.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the mo file sinh vien: " + duongDanFile;
        return kq;
    }

    string line;
    while (getline(ifs, line)) {
        string cleanLine = loaiBoKyTuXuongDong(line);
        if (catKhoangTrangHaiDau(cleanLine).empty()) {
            continue;
        }

        int soPhanTu = 0;
        string* parts = tachTheoDauGachDung(cleanLine, soPhanTu);
        if (parts == nullptr || soPhanTu != 4) {
            giaiPhongMangString(parts);
            ++kq.soDongLoi;
            continue;
        }

        SinhVien sv = taoSinhVien(
            catKhoangTrangHaiDau(parts[0]),
            catKhoangTrangHaiDau(parts[1]),
            catKhoangTrangHaiDau(parts[2]),
            catKhoangTrangHaiDau(parts[3])
        );
        giaiPhongMangString(parts);

        bool chenThanhCong = false;
        rootAVL = insertAVL(rootAVL, sv, chenThanhCong);
        giaiPhongSinhVien(sv);

        if (chenThanhCong) {
            ++kq.soDongHopLe;
        } else {
            ++kq.soDongLoi;
        }
    }

    ifs.close();
    kq.thanhCong = true;
    kq.thongBao = "Doc sinh vien xong (" + to_string(kq.soDongHopLe) +
                  " hop le, " + to_string(kq.soDongLoi) + " dong loi/trung).";
    return kq;
}

KetQuaFile docVaGanHocPhanAVL(const string& duongDanFile, AVLNode* rootAVL) {
    KetQuaFile kq;
    if (rootAVL == nullptr) {
        kq.thanhCong = false;
        kq.thongBao = "Cay AVL rong, can nap danh sach sinh vien truoc khi doc hoc phan.";
        return kq;
    }

    ifstream ifs(duongDanFile);
    if (!ifs.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the mo file hoc phan: " + duongDanFile;
        return kq;
    }

    string line;
    while (getline(ifs, line)) {
        string cleanLine = loaiBoKyTuXuongDong(line);
        if (catKhoangTrangHaiDau(cleanLine).empty()) {
            continue;
        }

        int soPhanTu = 0;
        string* parts = tachTheoDauGachDung(cleanLine, soPhanTu);
        if (parts == nullptr || soPhanTu != 5) {
            giaiPhongMangString(parts);
            ++kq.soDongLoi;
            continue;
        }

        string mssv = catKhoangTrangHaiDau(parts[0]);
        string maHP = catKhoangTrangHaiDau(parts[1]);
        string tenHP = catKhoangTrangHaiDau(parts[2]);
        int soTinChi = 0;
        float diemHe10 = 0.0f;

        bool hopLeSo = parseSoNguyenAnToan(parts[3], soTinChi) &&
                       parseSoThucFloatAnToan(parts[4], diemHe10);
        giaiPhongMangString(parts);

        if (!hopLeSo) {
            ++kq.soDongLoi;
            continue;
        }

        HocPhan* hpMoi = taoHocPhan(maHP, tenHP, soTinChi, diemHe10);
        if (hpMoi == nullptr) {
            ++kq.soDongLoi;
            continue;
        }

        AVLNode* svNode = searchAVL(rootAVL, mssv);
        if (svNode == nullptr) {
            delete hpMoi;
            ++kq.soDongLoi;
            continue;
        }

        themHocPhan(svNode->data.dsHocPhan, hpMoi);
        ++kq.soDongHopLe;
    }

    ifs.close();
    kq.thanhCong = true;
    kq.thongBao = "Doc hoc phan xong (" + to_string(kq.soDongHopLe) +
                  " hop le, " + to_string(kq.soDongLoi) + " dong loi/khong tim thay SV).";
    return kq;
}

KetQuaFile napDuLieuTongHopAVL(const string& fileSinhVien,
                                const string& fileHocPhan,
                                AVLNode*& rootAVL) {
    KetQuaFile kqSV = docVaNapSinhVienAVL(fileSinhVien, rootAVL);
    if (!kqSV.thanhCong) {
        return kqSV;
    }

    KetQuaFile kqHP = docVaGanHocPhanAVL(fileHocPhan, rootAVL);
    KetQuaFile tongHop;
    tongHop.thanhCong = kqHP.thanhCong;
    tongHop.soDongHopLe = kqSV.soDongHopLe + kqHP.soDongHopLe;
    tongHop.soDongLoi = kqSV.soDongLoi + kqHP.soDongLoi;
    tongHop.thongBao = kqSV.thongBao + " | " + kqHP.thongBao;
    return tongHop;
}

KetQuaFile napDuLieuTongHopBST(const string& fileSinhVien,
                                const string& fileHocPhan,
                                BSTNode*& rootBST) {
    KetQuaFile kq;
    ifstream ifsSV(fileSinhVien);
    if (!ifsSV.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the mo file sinh vien cho BST: " + fileSinhVien;
        return kq;
    }

    string line;
    while (getline(ifsSV, line)) {
        string cleanLine = loaiBoKyTuXuongDong(line);
        if (catKhoangTrangHaiDau(cleanLine).empty()) {
            continue;
        }

        int soPhanTu = 0;
        string* parts = tachTheoDauGachDung(cleanLine, soPhanTu);
        if (parts == nullptr || soPhanTu != 4) {
            giaiPhongMangString(parts);
            ++kq.soDongLoi;
            continue;
        }

        SinhVien sv = taoSinhVien(
            catKhoangTrangHaiDau(parts[0]),
            catKhoangTrangHaiDau(parts[1]),
            catKhoangTrangHaiDau(parts[2]),
            catKhoangTrangHaiDau(parts[3])
        );
        giaiPhongMangString(parts);

        bool chenThanhCong = false;
        rootBST = insertBST(rootBST, sv, chenThanhCong);
        giaiPhongSinhVien(sv);

        if (chenThanhCong) {
            ++kq.soDongHopLe;
        } else {
            ++kq.soDongLoi;
        }
    }
    ifsSV.close();

    ifstream ifsHP(fileHocPhan);
    if (!ifsHP.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the mo file hoc phan cho BST: " + fileHocPhan;
        return kq;
    }

    while (getline(ifsHP, line)) {
        string cleanLine = loaiBoKyTuXuongDong(line);
        if (catKhoangTrangHaiDau(cleanLine).empty()) {
            continue;
        }

        int soPhanTu = 0;
        string* parts = tachTheoDauGachDung(cleanLine, soPhanTu);
        if (parts == nullptr || soPhanTu != 5) {
            giaiPhongMangString(parts);
            ++kq.soDongLoi;
            continue;
        }

        string mssv = catKhoangTrangHaiDau(parts[0]);
        string maHP = catKhoangTrangHaiDau(parts[1]);
        string tenHP = catKhoangTrangHaiDau(parts[2]);
        int soTinChi = 0;
        float diemHe10 = 0.0f;

        bool hopLeSo = parseSoNguyenAnToan(parts[3], soTinChi) &&
                       parseSoThucFloatAnToan(parts[4], diemHe10);
        giaiPhongMangString(parts);

        if (!hopLeSo) {
            ++kq.soDongLoi;
            continue;
        }

        HocPhan* hpMoi = taoHocPhan(maHP, tenHP, soTinChi, diemHe10);
        if (hpMoi == nullptr) {
            ++kq.soDongLoi;
            continue;
        }

        BSTNode* svNode = searchBST(rootBST, mssv);
        if (svNode == nullptr) {
            delete hpMoi;
            ++kq.soDongLoi;
            continue;
        }

        themHocPhan(svNode->data.dsHocPhan, hpMoi);
        ++kq.soDongHopLe;
    }
    ifsHP.close();

    kq.thanhCong = true;
    kq.thongBao = "Nap BST xong (" + to_string(kq.soDongHopLe) +
                  " hop le, " + to_string(kq.soDongLoi) + " dong loi/trung).";
    return kq;
}

KetQuaFile ghiDuLieuRaFileAVL(AVLNode* rootAVL,
                              const string& fileSinhVien,
                              const string& fileHocPhan) {
    KetQuaFile kq;
    ofstream ofsSV(fileSinhVien);
    if (!ofsSV.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the ghi file sinh vien: " + fileSinhVien;
        return kq;
    }

    ofstream ofsHP(fileHocPhan);
    if (!ofsHP.is_open()) {
        ofsSV.close();
        kq.thanhCong = false;
        kq.thongBao = "Khong the ghi file hoc phan: " + fileHocPhan;
        return kq;
    }

    int tongSV = 0;
    int tongHP = 0;
    ghiDeQuyAVL(rootAVL, ofsSV, ofsHP, tongSV, tongHP);

    ofsSV.close();
    ofsHP.close();

    kq.thanhCong = true;
    kq.soDongHopLe = tongSV + tongHP;
    kq.thongBao = "Da ghi " + to_string(tongSV) + " sinh vien va " +
                  to_string(tongHP) + " hoc phan ra file.";
    return kq;
}

void taoBoDuLieuLonNgauNhien(int soLuong,
                              SinhVien*& dsSinhVien,
                              int& soLuongThucTe,
                              const string& duongDanFileGhi) {
    giaiPhongMangSinhVien(dsSinhVien, soLuongThucTe);
    soLuongThucTe = 0;

    if (soLuong < SO_LUONG_DU_LIEU_LON_MAC_DINH) {
        soLuong = SO_LUONG_DU_LIEU_LON_MAC_DINH;
    }

    static const string HO_MAU[] = {"Nguyen", "Tran", "Le", "Pham", "Hoang", "Huynh", "Phan", "Vu"};
    static const string TEN_MAU[] = {"An", "Binh", "Chi", "Dung", "Giang", "Ha", "Khoi", "Linh", "Minh", "Nam"};
    static const string LOP_MAU[] = {"CNTT01", "CNTT02", "CNTT03", "IT02"};
    static const string DOB_MAU[] = {"15/03/2005", "22/07/2005", "09/11/2004", "18/06/2005"};

    SinhVien* arr = new SinhVien[soLuong];
    for (int i = 0; i < soLuong; ++i) {
        string mssv = taoMaSVChuan(i + 1);
        string hoTen = HO_MAU[i % 8] + " Thi " + TEN_MAU[(i * 3) % 10] + " " + to_string(i + 1);
        string lop = LOP_MAU[i % 4];
        string ngaySinh = DOB_MAU[i % 4];
        arr[i] = taoSinhVien(mssv, hoTen, lop, ngaySinh);
    }

    random_device rd;
    mt19937 rng(rd());
    xaoTronMangSinhVien(arr, soLuong, rng);

    if (!duongDanFileGhi.empty()) {
        ofstream ofs(duongDanFileGhi);
        if (ofs.is_open()) {
            for (int i = 0; i < soLuong; ++i) {
                ofs << arr[i].mssv << '|'
                    << arr[i].hoTen << '|'
                    << arr[i].lop << '|'
                    << arr[i].ngaySinh << '\n';
            }
            ofs.close();
        }
    }

    dsSinhVien = arr;
    soLuongThucTe = soLuong;
}

void thucNghiemAVLvaBST(int soLuong,
                         bool duLieuTangDan,
                         const string& duongDanFileGhi) {
    if (soLuong < SO_LUONG_DU_LIEU_LON_MAC_DINH) {
        soLuong = SO_LUONG_DU_LIEU_LON_MAC_DINH;
    }

    SinhVien* dsTest = nullptr;
    int nThucTe = 0;

    if (duLieuTangDan) {
        dsTest = new SinhVien[soLuong];
        nThucTe = soLuong;
        for (int i = 0; i < soLuong; ++i) {
            dsTest[i] = taoSinhVien(taoMaSVChuan(i + 1),
                                      "Sinh Vien " + to_string(i + 1),
                                      "CNTT01",
                                      "15/03/2005");
        }
        if (!duongDanFileGhi.empty()) {
            ofstream ofs(duongDanFileGhi);
            if (ofs.is_open()) {
                for (int i = 0; i < soLuong; ++i) {
                    ofs << dsTest[i].mssv << '|'
                        << dsTest[i].hoTen << '|'
                        << dsTest[i].lop << '|'
                        << dsTest[i].ngaySinh << '\n';
                }
                ofs.close();
            }
        }
    } else {
        taoBoDuLieuLonNgauNhien(soLuong, dsTest, nThucTe, duongDanFileGhi);
    }

    AVLNode* rootAVL = nullptr;
    BSTNode* rootBST = nullptr;

    auto tChenAVLBeg = chrono::steady_clock::now();
    for (int i = 0; i < nThucTe; ++i) {
        bool ok = false;
        rootAVL = insertAVL(rootAVL, dsTest[i], ok);
    }
    auto tChenAVLEnd = chrono::steady_clock::now();

    auto tChenBSTBeg = chrono::steady_clock::now();
    for (int i = 0; i < nThucTe; ++i) {
        bool ok = false;
        rootBST = insertBST(rootBST, dsTest[i], ok);
    }
    auto tChenBSTEnd = chrono::steady_clock::now();

    string khoaCanTim = taoMaSVChuan(nThucTe);

    auto tTimAVLBeg = chrono::steady_clock::now();
    for (int k = 0; k < SO_LAN_TIM_KIEM_THUC_NGHIEM; ++k) {
        searchAVL(rootAVL, khoaCanTim);
    }
    auto tTimAVLEnd = chrono::steady_clock::now();

    auto tTimBSTBeg = chrono::steady_clock::now();
    for (int k = 0; k < SO_LAN_TIM_KIEM_THUC_NGHIEM; ++k) {
        searchBST(rootBST, khoaCanTim);
    }
    auto tTimBSTEnd = chrono::steady_clock::now();

    double msChenAVL = chrono::duration<double, milli>(tChenAVLEnd - tChenAVLBeg).count();
    double msChenBST = chrono::duration<double, milli>(tChenBSTEnd - tChenBSTBeg).count();
    double msTimAVL = chrono::duration<double, milli>(tTimAVLEnd - tTimAVLBeg).count();
    double msTimBST = chrono::duration<double, milli>(tTimBSTEnd - tTimBSTBeg).count();

    cout << "\n--- KET QUA THUC NGHIEM (N = " << nThucTe
         << (duLieuTangDan ? ", MSSV tang dan" : ", sinh ngau nhien") << ") ---\n";
    cout << "Chieu cao AVL : " << getHeight(rootAVL)
         << " | Chieu cao BST: " << getHeightBST(rootBST) << '\n';
    cout << fixed << setprecision(3);
    cout << "Thoi gian chen " << nThucTe << " ban ghi: AVL = " << msChenAVL
         << " ms | BST = " << msChenBST << " ms\n";
    cout << "Thoi gian tim kiem (" << SO_LAN_TIM_KIEM_THUC_NGHIEM
         << " lan): AVL = " << msTimAVL << " ms | BST = " << msTimBST << " ms\n";

    giaiPhongAVL(rootAVL);
    giaiPhongBST(rootBST);
    giaiPhongMangSinhVien(dsTest, nThucTe);
}