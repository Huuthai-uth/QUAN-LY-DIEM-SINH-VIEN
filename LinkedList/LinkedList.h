#pragma once
#include "../HocPhan/HocPhan.h"
#include <string>

// Các thao tác cơ bản trên danh sách liên kết đơn học phần
void themHocPhan(HocPhan*& head, HocPhan* hpMoi);
bool xoaHocPhan(HocPhan*& head, const std::string& maHP);
HocPhan* timHocPhan(HocPhan* head, const std::string& maHP);
bool suaDiemHocPhan(HocPhan* head, const std::string& maHP, float diemMoi);

// Duyệt xuất và giải phóng bộ nhớ DSLK
void xuatDanhSachHocPhan(const HocPhan* head);
int demSoHocPhan(const HocPhan* head);
void giaiPhongDSLK(HocPhan*& head);

// Sao chép sâu (Deep Copy) danh sách học phần (cần dùng khi xóa nút có 2 con trên cây AVL/BST)
HocPhan* saoChepDSLK(const HocPhan* head);