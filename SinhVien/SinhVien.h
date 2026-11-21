#ifndef SINHVIEN_H
#define SINHVIEN_H

#include "LinkedList.h"

using namespace std;

struct SinhVien
{
    string MSSV;
    string HoTen;
    string Lop;
    string NgaySinh;
    DanhSachHocPhan dsHocPhan;

    SinhVien();
    SinhVien(const SinhVien& sv);
    SinhVien& operator=(const SinhVien& sv);
    ~SinhVien();
};

bool KiemTraNgaySinh(const string& ngaySinh);
bool KiemTraSinhVienHopLe(const SinhVien& sv);
void NhapSinhVien(SinhVien& sv);
void XuatSinhVien(const SinhVien& sv);

#endif
