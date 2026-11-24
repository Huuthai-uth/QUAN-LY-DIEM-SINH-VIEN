#pragma once
#include <string>
#include "../SinhVien/SinhVien.h"
#include "../AVL/AVL.h"
#include "../BST/BST.h"

struct BanGhiXepHangSV {
    SinhVien sv;
    double gpaHe10 = 0.0;
    double gpaHe4 = 0.0;
    int soTinChi = 0;
};

// Phan hoach mang BanGhiXepHangSV giam dan theo GPA he 10 (hoac he 4)
int phanHoachQuickSort(BanGhiXepHangSV* arr, int low, int high, bool uuTienHe4 = false);

// Thuat toan Quick Sort sap xep giam dan theo GPA
void quickSortGiamDan(BanGhiXepHangSV* arr, int low, int high, bool uuTienHe4 = false);

// Trich xuat sinh vien tu cay AVL (co the loc theo lop, neu tenLop rong thi lay tat ca)
BanGhiXepHangSV* trichXuatTuAVL(AVLNode* root, const std::string& tenLop, int& soLuong);

// Trich xuat sinh vien tu cay BST (phuc vu so sanh thuc nghiem)
BanGhiXepHangSV* trichXuatTuBST(BSTNode* root, const std::string& tenLop, int& soLuong);

// Sap xep danh sach sinh vien mot lop giam dan theo diem trung binh
BanGhiXepHangSV* sapXepLopGiamDanAVL(AVLNode* root, const std::string& tenLop,
                                     int& soLuong, bool uuTienHe4 = false);

// Giai phong mang BanGhiXepHangSV va danh sach hoc phan ben trong
void giaiPhongMangXepHang(BanGhiXepHangSV*& arr, int& soLuong);