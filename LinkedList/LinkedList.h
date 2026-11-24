#pragma once
#include "../HocPhan/HocPhan.h"
#include <string>

// Cac thao tac co ban tren danh sach lien ket don hoc phan
void themHocPhan(HocPhan*& head, HocPhan* hpMoi);
bool xoaHocPhan(HocPhan*& head, const std::string& maHP);
HocPhan* timHocPhan(HocPhan* head, const std::string& maHP);
bool suaDiemHocPhan(HocPhan* head, const std::string& maHP, float diemMoi);

// Duyet xuat va giai phong bo nho DSLK
void xuatDanhSachHocPhan(const HocPhan* head);
int demSoHocPhan(const HocPhan* head);
void giaiPhongDSLK(HocPhan*& head);

// Sao chep sau (Deep Copy) danh sach hoc phan
HocPhan* saoChepDSLK(const HocPhan* head);