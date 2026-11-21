#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <string>
#include "QuanLyDiem.h"

int partitionGPA(SinhVien* arr, int low, int high);
void quickSortGPA(SinhVien* arr, int low, int high);
void sapXepGiamDan(DanhSachSV& ds);
void sapXepTheoLopGiamDanGPA(const DanhSachSV& ds, const std::string& tenLop, DanhSachSV& ketQua);

#endif
