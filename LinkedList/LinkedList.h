#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "HocPhan.h"

using namespace std;

struct NodeHocPhan
{
    HocPhan data;
    NodeHocPhan* next;

    NodeHocPhan(const HocPhan& hp);
};

struct DanhSachHocPhan
{
    NodeHocPhan* head;
    int soLuong;

    DanhSachHocPhan();
};

void KhoiTaoDanhSach(DanhSachHocPhan& ds);
bool ThemHocPhan(DanhSachHocPhan& ds, const HocPhan& hp);
bool XoaHocPhan(DanhSachHocPhan& ds, const string& maHP);
NodeHocPhan* TimHocPhan(DanhSachHocPhan& ds, const string& maHP);
const NodeHocPhan* TimHocPhan(const DanhSachHocPhan& ds, const string& maHP);
bool SuaHocPhan(DanhSachHocPhan& ds, const string& maHP, const HocPhan& hocPhanMoi);
void InDanhSachHocPhan(const DanhSachHocPhan& ds);
int DemHocPhan(const DanhSachHocPhan& ds);
void GiaiPhongDanhSach(DanhSachHocPhan& ds);
void SaoChepDanhSach(DanhSachHocPhan& dich, const DanhSachHocPhan& nguon);

#endif
