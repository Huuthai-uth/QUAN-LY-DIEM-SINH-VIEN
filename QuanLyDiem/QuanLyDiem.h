#ifndef QUANLYDIEM_H
#define QUANLYDIEM_H

#include <string>
#include "Student.h"

struct DanhSachSV {
    SinhVien* data = nullptr;
    int size = 0;
    int capacity = 0;
};

void khoiTaoDanhSach(DanhSachSV& ds, int initCap = 4);
void giaiPhongDanhSach(DanhSachSV& ds);
void themVaoDanhSach(DanhSachSV& ds, const SinhVien& sv);
bool xoaKhoiDanhSach(DanhSachSV& ds, int index);
int timViTriSV(const DanhSachSV& ds, const std::string& maSV);
std::string toLowerStr(const std::string& s);

void themSinhVien(DanhSachSV& ds);
void xoaSinhVien(DanhSachSV& ds);
void timKiemSinhVien(const DanhSachSV& ds);
void quanLyHocPhan(DanhSachSV& ds);
void nhapVaSuaDiem(DanhSachSV& ds);

#endif
