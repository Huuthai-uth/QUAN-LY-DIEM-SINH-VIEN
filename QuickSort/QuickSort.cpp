#include "QuickSort.h"
#include "../QuanLyDiem/QuanLyDiem.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace {
    void hoanViBanGhi(BanGhiXepHangSV& a, BanGhiXepHangSV& b) {
        if (&a == &b) {
            return;
        }
        BanGhiXepHangSV temp = a;
        a = b;
        b = temp;
    }

    double layKhoaSapXep(const BanGhiXepHangSV& item, bool uuTienHe4) {
        return uuTienHe4 ? item.gpaHe4 : item.gpaHe10;
    }

    void demSoLuongPhuHopAVL(AVLNode* node, const string& tenLop, int& count) {
        if (node == nullptr) {
            return;
        }
        demSoLuongPhuHopAVL(node->left, tenLop, count);
        if (tenLop.empty() || node->data.lop == tenLop) {
            ++count;
        }
        demSoLuongPhuHopAVL(node->right, tenLop, count);
    }

    void ghiDuLieuAVL(AVLNode* node, const string& tenLop, BanGhiXepHangSV* arr, int& idx) {
        if (node == nullptr) {
            return;
        }
        ghiDuLieuAVL(node->left, tenLop, arr, idx);
        if (tenLop.empty() || node->data.lop == tenLop) {
            arr[idx].sv.mssv = node->data.mssv;
            arr[idx].sv.hoTen = node->data.hoTen;
            arr[idx].sv.lop = node->data.lop;
            arr[idx].sv.ngaySinh = node->data.ngaySinh;
            arr[idx].sv.dsHocPhan = saoChepDSLK(node->data.dsHocPhan);

            KetQuaDiem kq = tinhKetQuaHocTap(arr[idx].sv);
            arr[idx].gpaHe10 = kq.gpaHe10;
            arr[idx].gpaHe4 = kq.gpaHe4;
            arr[idx].soTinChi = kq.tongTinChi;
            ++idx;
        }
        ghiDuLieuAVL(node->right, tenLop, arr, idx);
    }

    void demSoLuongPhuHopBST(BSTNode* node, const string& tenLop, int& count) {
        if (node == nullptr) {
            return;
        }
        demSoLuongPhuHopBST(node->left, tenLop, count);
        if (tenLop.empty() || node->data.lop == tenLop) {
            ++count;
        }
        demSoLuongPhuHopBST(node->right, tenLop, count);
    }

    void ghiDuLieuBST(BSTNode* node, const string& tenLop, BanGhiXepHangSV* arr, int& idx) {
        if (node == nullptr) {
            return;
        }
        ghiDuLieuBST(node->left, tenLop, arr, idx);
        if (tenLop.empty() || node->data.lop == tenLop) {
            arr[idx].sv.mssv = node->data.mssv;
            arr[idx].sv.hoTen = node->data.hoTen;
            arr[idx].sv.lop = node->data.lop;
            arr[idx].sv.ngaySinh = node->data.ngaySinh;
            arr[idx].sv.dsHocPhan = saoChepDSLK(node->data.dsHocPhan);

            KetQuaDiem kq = tinhKetQuaHocTap(arr[idx].sv);
            arr[idx].gpaHe10 = kq.gpaHe10;
            arr[idx].gpaHe4 = kq.gpaHe4;
            arr[idx].soTinChi = kq.tongTinChi;
            ++idx;
        }
        ghiDuLieuBST(node->right, tenLop, arr, idx);
    }
}

int phanHoachQuickSort(BanGhiXepHangSV* arr, int low, int high, bool uuTienHe4) {
    if (arr == nullptr || low >= high) {
        return low;
    }

    // Chon phan tu o giua lam pivot de han che suy bien O(n^2) tren du lieu co thu tu
    int mid = low + (high - low) / 2;
    hoanViBanGhi(arr[mid], arr[high]);

    double pivot = layKhoaSapXep(arr[high], uuTienHe4);
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (layKhoaSapXep(arr[j], uuTienHe4) >= pivot) {
            ++i;
            hoanViBanGhi(arr[i], arr[j]);
        }
    }

    hoanViBanGhi(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortGiamDan(BanGhiXepHangSV* arr, int low, int high, bool uuTienHe4) {
    if (arr == nullptr || low >= high) {
        return;
    }

    int pi = phanHoachQuickSort(arr, low, high, uuTienHe4);
    if (pi - 1 > low) {
        quickSortGiamDan(arr, low, pi - 1, uuTienHe4);
    }
    if (pi + 1 < high) {
        quickSortGiamDan(arr, pi + 1, high, uuTienHe4);
    }
}

BanGhiXepHangSV* trichXuatTuAVL(AVLNode* root, const string& tenLop, int& soLuong) {
    soLuong = 0;
    if (root == nullptr) {
        return nullptr;
    }

    demSoLuongPhuHopAVL(root, tenLop, soLuong);
    if (soLuong <= 0) {
        soLuong = 0;
        return nullptr;
    }

    BanGhiXepHangSV* arr = new BanGhiXepHangSV[soLuong];
    int idx = 0;
    ghiDuLieuAVL(root, tenLop, arr, idx);
    return arr;
}

BanGhiXepHangSV* trichXuatTuBST(BSTNode* root, const string& tenLop, int& soLuong) {
    soLuong = 0;
    if (root == nullptr) {
        return nullptr;
    }

    demSoLuongPhuHopBST(root, tenLop, soLuong);
    if (soLuong <= 0) {
        soLuong = 0;
        return nullptr;
    }

    BanGhiXepHangSV* arr = new BanGhiXepHangSV[soLuong];
    int idx = 0;
    ghiDuLieuBST(root, tenLop, arr, idx);
    return arr;
}

BanGhiXepHangSV* sapXepLopGiamDanAVL(AVLNode* root, const string& tenLop,
                                     int& soLuong, bool uuTienHe4) {
    BanGhiXepHangSV* arr = trichXuatTuAVL(root, tenLop, soLuong);
    if (arr != nullptr && soLuong > 1) {
        quickSortGiamDan(arr, 0, soLuong - 1, uuTienHe4);
    }
    return arr;
}

void giaiPhongMangXepHang(BanGhiXepHangSV*& arr, int& soLuong) {
    if (arr != nullptr) {
        for (int i = 0; i < soLuong; ++i) {
            giaiPhongSinhVien(arr[i].sv);
        }
        delete[] arr;
        arr = nullptr;
    }
    soLuong = 0;
}