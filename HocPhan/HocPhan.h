#pragma once
#include <string>

struct HocPhan {
    std::string maHP;
    std::string tenHP;
    int soTinChi;
    float diemHe10;
    HocPhan* next;
};

// Kiem tra tinh hop le cua thong tin hoc phan
bool kiemTraMaHP(const std::string& maHP);
bool kiemTraTenHP(const std::string& tenHP);
bool kiemTraSoTinChi(int soTinChi);
bool kiemTraDiem(float diem);

// Khoi tao, nhap va xuat thong tin 1 hoc phan
HocPhan* taoHocPhan(const std::string& maHP, const std::string& tenHP,
                    int soTinChi, float diemHe10);
HocPhan* nhapHocPhan();
void xuatHocPhan(const HocPhan* hp);