#pragma once
#include <string>
#include "../SinhVien/SinhVien.h"
#include "../HocPhan/HocPhan.h"
#include "../LinkedList/LinkedList.h"

struct KetQuaDiem {
    double gpaHe10 = 0.0;
    double gpaHe4 = 0.0;
    std::string xepLoai;
    int tongTinChi = 0;
};

// Quy doi diem he 10 sang diem he 4
double quyDoiDiemHe4(float diem10);

// Xep loai hoc luc theo GPA he 10
std::string xepLoaiHocLuc(double gpa10);

// Tinh tong hop GPA he 10, GPA he 4, tong tin chi va xep loai cua 1 sinh vien
KetQuaDiem tinhKetQuaHocTap(const SinhVien& sv);

// In bang diem ca nhan day du
void inBangDiemSinhVien(const SinhVien& sv);

// Them hoc phan hoac sua diem hoc phan cho 1 sinh vien cu the
bool themHocPhanChoSinhVien(SinhVien& sv, const std::string& maHP, const std::string& tenHP,
                           int soTinChi, float diemHe10);
bool suaDiemChoSinhVien(SinhVien& sv, const std::string& maHP, float diemMoi);