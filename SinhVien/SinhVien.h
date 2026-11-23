#pragma once
#include "../LinkedList/LinkedList.h"
#include <string>

struct SinhVien {
    std::string mssv;
    std::string hoTen;
    std::string lop;
    std::string ngaySinh;
    HocPhan* dsHocPhan; // Danh sách liên kết đơn các học phần đã học
};

// Kiểm tra dữ liệu sinh viên hợp lệ
bool kiemTraMSSV(const std::string& mssv);
bool kiemTraNgaySinh(const std::string& ngaySinh);
bool kiemTraSinhVienHopLe(const SinhVien& sv);

// Nhập, xuất và giải phóng dữ liệu 1 sinh viên
SinhVien taoSinhVien(const std::string& mssv, const std::string& hoTen,
                     const std::string& lop, const std::string& ngaySinh);
SinhVien nhapSinhVien();
void xuatSinhVien(const SinhVien& sv);
void giaiPhongSinhVien(SinhVien& sv);