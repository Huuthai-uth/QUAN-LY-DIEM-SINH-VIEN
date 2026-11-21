#include "QuickSort.h"

using namespace std;

static void hoanViSV(SinhVien& a, SinhVien& b) {
    SinhVien temp;
    saoChepSinhVien(temp, a);
    saoChepSinhVien(a, b);
    saoChepSinhVien(b, temp);
    giaiPhongSinhVien(temp);
}

int partitionGPA(SinhVien* arr, int low, int high) {
    double pivot = arr[high].gpa10;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].gpa10 >= pivot) {
            ++i;
            hoanViSV(arr[i], arr[j]);
        }
    }
    hoanViSV(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortGPA(SinhVien* arr, int low, int high) {
    if (low < high) {
        int pi = partitionGPA(arr, low, high);
        quickSortGPA(arr, low, pi - 1);
        quickSortGPA(arr, pi + 1, high);
    }
}

void sapXepGiamDan(DanhSachSV& ds) {
    for (int i = 0; i < ds.size; ++i) {
        capNhatGPA(ds.data[i]);
    }
    if (ds.size > 1) {
        quickSortGPA(ds.data, 0, ds.size - 1);
    }
}

void sapXepTheoLopGiamDanGPA(const DanhSachSV& ds, const string& tenLop, DanhSachSV& ketQua) {
    khoiTaoDanhSach(ketQua, 4);
    for (int i = 0; i < ds.size; ++i) {
        if (ds.data[i].lop == tenLop) {
            themVaoDanhSach(ketQua, ds.data[i]);
            capNhatGPA(ketQua.data[ketQua.size - 1]);
        }
    }
    if (ketQua.size > 1) {
        quickSortGPA(ketQua.data, 0, ketQua.size - 1);
    }
}
