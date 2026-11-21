#ifndef HOCPHAN_H
#define HOCPHAN_H

#include <iostream>
#include <string>

using namespace std;

struct HocPhan
{
    string MaHP;
    string TenHP;
    int SoTinChi;
    double Diem;
    bool CoDiem;

    HocPhan();
};

bool KiemTraHocPhanHopLe(const HocPhan& hp);
void NhapHocPhan(HocPhan& hp);
void XuatHocPhan(const HocPhan& hp);

#endif
