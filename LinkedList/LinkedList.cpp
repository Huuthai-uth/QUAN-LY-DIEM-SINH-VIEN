#include "LinkedList.h"

using namespace std;

NodeHocPhan::NodeHocPhan(const HocPhan& hp)
{
    data = hp;
    next = NULL;
}

DanhSachHocPhan::DanhSachHocPhan()
{
    head = NULL;
    soLuong = 0;
}

void KhoiTaoDanhSach(DanhSachHocPhan& ds)
{
    ds.head = NULL;
    ds.soLuong = 0;
}

NodeHocPhan* TimHocPhan(DanhSachHocPhan& ds, const string& maHP)
{
    NodeHocPhan* p = ds.head;

    while (p != NULL)
    {
        if (p->data.MaHP == maHP)
            return p;

        p = p->next;
    }

    return NULL;
}

const NodeHocPhan* TimHocPhan(const DanhSachHocPhan& ds, const string& maHP)
{
    const NodeHocPhan* p = ds.head;

    while (p != NULL)
    {
        if (p->data.MaHP == maHP)
            return p;

        p = p->next;
    }

    return NULL;
}

bool ThemHocPhan(DanhSachHocPhan& ds, const HocPhan& hp)
{
    if (!KiemTraHocPhanHopLe(hp))
        return false;

    if (TimHocPhan(ds, hp.MaHP) != NULL)
        return false;

    NodeHocPhan* nodeMoi = new NodeHocPhan(hp);

    if (ds.head == NULL)
    {
        ds.head = nodeMoi;
    }
    else
    {
        NodeHocPhan* p = ds.head;

        while (p->next != NULL)
            p = p->next;

        p->next = nodeMoi;
    }

    ds.soLuong++;
    return true;
}

bool XoaHocPhan(DanhSachHocPhan& ds, const string& maHP)
{
    if (ds.head == NULL)
        return false;

    if (ds.head->data.MaHP == maHP)
    {
        NodeHocPhan* temp = ds.head;
        ds.head = ds.head->next;
        delete temp;
        ds.soLuong--;
        return true;
    }

    NodeHocPhan* p = ds.head;

    while (p->next != NULL && p->next->data.MaHP != maHP)
        p = p->next;

    if (p->next == NULL)
        return false;

    NodeHocPhan* temp = p->next;
    p->next = temp->next;
    delete temp;
    ds.soLuong--;

    return true;
}

bool SuaHocPhan(DanhSachHocPhan& ds, const string& maHP, const HocPhan& hocPhanMoi)
{
    NodeHocPhan* p = TimHocPhan(ds, maHP);

    if (p == NULL)
        return false;

    if (!KiemTraHocPhanHopLe(hocPhanMoi))
        return false;

    // Khong cho doi ma hoc phan thanh ma da ton tai o node khac.
    if (hocPhanMoi.MaHP != maHP && TimHocPhan(ds, hocPhanMoi.MaHP) != NULL)
        return false;

    p->data = hocPhanMoi;
    return true;
}

void InDanhSachHocPhan(const DanhSachHocPhan& ds)
{
    if (ds.head == NULL)
    {
        cout << "Sinh vien chua co hoc phan nao.\n";
        return;
    }

    cout << "\n========== DANH SACH HOC PHAN ==========\n";

    const NodeHocPhan* p = ds.head;
    int stt = 1;

    while (p != NULL)
    {
        cout << "\nHoc phan " << stt++ << ":\n";
        XuatHocPhan(p->data);
        p = p->next;
    }
}

int DemHocPhan(const DanhSachHocPhan& ds)
{
    return ds.soLuong;
}

void GiaiPhongDanhSach(DanhSachHocPhan& ds)
{
    NodeHocPhan* p = ds.head;

    while (p != NULL)
    {
        NodeHocPhan* temp = p;
        p = p->next;
        delete temp;
    }

    ds.head = NULL;
    ds.soLuong = 0;
}

void SaoChepDanhSach(DanhSachHocPhan& dich, const DanhSachHocPhan& nguon)
{
    GiaiPhongDanhSach(dich);

    const NodeHocPhan* p = nguon.head;

    while (p != NULL)
    {
        ThemHocPhan(dich, p->data);
        p = p->next;
    }
}
