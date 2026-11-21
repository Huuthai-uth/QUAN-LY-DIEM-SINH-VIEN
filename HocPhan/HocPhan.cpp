#include "HocPhan.h"
#include <limits>

using namespace std;

HocPhan::HocPhan()
{
    MaHP = "";
    TenHP = "";
    SoTinChi = 0;
    Diem = 0;
    CoDiem = false;
}

bool KiemTraHocPhanHopLe(const HocPhan& hp)
{
    if (hp.MaHP.empty() || hp.TenHP.empty())
        return false;

    if (hp.SoTinChi <= 0)
        return false;

    if (hp.CoDiem && (hp.Diem < 0 || hp.Diem > 10))
        return false;

    return true;
}

void NhapHocPhan(HocPhan& hp)
{
    cout << "Nhap ma hoc phan: ";
    getline(cin >> ws, hp.MaHP);

    cout << "Nhap ten hoc phan: ";
    getline(cin, hp.TenHP);

    while (true)
    {
        cout << "Nhap so tin chi: ";
        if (cin >> hp.SoTinChi && hp.SoTinChi > 0)
            break;

        cout << "So tin chi phai la so nguyen duong. Nhap lai!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int luaChon;
    while (true)
    {
        cout << "Hoc phan da co diem chua? (1: Co, 0: Chua): ";
        if (cin >> luaChon && (luaChon == 0 || luaChon == 1))
            break;

        cout << "Lua chon khong hop le. Nhap lai!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    hp.CoDiem = (luaChon == 1);

    if (hp.CoDiem)
    {
        while (true)
        {
            cout << "Nhap diem (0 - 10): ";
            if (cin >> hp.Diem && hp.Diem >= 0 && hp.Diem <= 10)
                break;

            cout << "Diem phai nam trong khoang 0 den 10. Nhap lai!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else
    {
        hp.Diem = 0;
    }
}

void XuatHocPhan(const HocPhan& hp)
{
    cout << "Ma hoc phan : " << hp.MaHP << '\n';
    cout << "Ten hoc phan: " << hp.TenHP << '\n';
    cout << "So tin chi  : " << hp.SoTinChi << '\n';

    if (hp.CoDiem)
        cout << "Diem        : " << hp.Diem << '\n';
    else
        cout << "Diem        : Chua co diem\n";
}
