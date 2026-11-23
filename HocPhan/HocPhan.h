#pragma once
#include <string>

struct HocPhan {
    std::string maHP;
    int soTinChi;
    float diemHe10;
    HocPhan* next;
};

// Kiểm tra tính hợp lệ của thông tin học phần
bool kiemTraMaHP(const std::string& maHP);
bool kiemTraSoTinChi(int soTinChi);
bool kiemTraDiem(float diem);

// Khởi tạo, nhập và xuất thông tin 1 học phần
HocPhan* taoHocPhan(const std::string& maHP, int soTinChi, float diemHe10);
HocPhan* nhapHocPhan();
void xuatHocPhan(const HocPhan* hp);