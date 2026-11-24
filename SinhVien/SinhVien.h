#pragma once
#include "../LinkedList/LinkedList.h"
#include <string>

struct SinhVien {
    std::string mssv;
    std::string hoTen;
    std::string lop;
    std::string ngaySinh;
    HocPhan* dsHocPhan; // Danh sach lien ket don cac hoc phan da hoc
};

// Kiem tra du lieu sinh vien hop le
bool kiemTraMSSV(const std::string& mssv);
bool kiemTraChuoiKhongRong(const std::string& str, size_t maxLen = 100);
bool kiemTraNgaySinh(const std::string& ngaySinh);
bool kiemTraSinhVienHopLe(const SinhVien& sv);

// Nhap, xuat va giai phong du lieu 1 sinh vien
SinhVien taoSinhVien(const std::string& mssv, const std::string& hoTen,
                     const std::string& lop, const std::string& ngaySinh);
SinhVien nhapSinhVien();
void xuatSinhVien(const SinhVien& sv);
void giaiPhongSinhVien(SinhVien& sv);