#include "HocPhan.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <limits>

using namespace std;

bool kiemTraMaHP(const string& maHP) {
    if (maHP.empty() || maHP.length() > 20) {
        return false;
    }
    for (char c : maHP) {
        if (!isalnum(static_cast<unsigned char>(c)) && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

bool kiemTraTenHP(const string& tenHP) {
    if (tenHP.empty() || tenHP.length() > 100) {
        return false;
    }
    bool coKyTuKhongRong = false;
    for (char c : tenHP) {
        if (!isspace(static_cast<unsigned char>(c))) {
            coKyTuKhongRong = true;
            break;
        }
    }
    return coKyTuKhongRong;
}

bool kiemTraSoTinChi(int soTinChi) {
    return soTinChi > 0 && soTinChi <= 15;
}

bool kiemTraDiem(float diem) {
    return isfinite(diem) && diem >= 0.0f && diem <= 10.0f;
}

HocPhan* taoHocPhan(const string& maHP, const string& tenHP,
                    int soTinChi, float diemHe10) {
    if (!kiemTraMaHP(maHP) || !kiemTraTenHP(tenHP) ||
        !kiemTraSoTinChi(soTinChi) || !kiemTraDiem(diemHe10)) {
        return nullptr;
    }
    HocPhan* hp = new HocPhan;
    hp->maHP = maHP;
    hp->tenHP = tenHP;
    hp->soTinChi = soTinChi;
    hp->diemHe10 = diemHe10;
    hp->next = nullptr;
    return hp;
}

HocPhan* nhapHocPhan() {
    string maHP;
    string tenHP;
    int soTinChi = 0;
    float diemHe10 = 0.0f;

    while (true) {
        cout << "Nhap ma hoc phan: ";
        getline(cin >> ws, maHP);
        if (kiemTraMaHP(maHP)) {
            break;
        }
        cout << "Ma hoc phan khong hop le! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap ten hoc phan: ";
        getline(cin >> ws, tenHP);
        if (kiemTraTenHP(tenHP)) {
            break;
        }
        cout << "Ten hoc phan khong hop le! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap so tin chi (1 - 15): ";
        if (cin >> soTinChi && kiemTraSoTinChi(soTinChi)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << "So tin chi khong hop le! Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Nhap diem he 10 (0.0 - 10.0): ";
        if (cin >> diemHe10 && kiemTraDiem(diemHe10)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << "Diem khong hop le! Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return taoHocPhan(maHP, tenHP, soTinChi, diemHe10);
}

void xuatHocPhan(const HocPhan* hp) {
    if (hp == nullptr) {
        return;
    }
    cout << left << setw(12) << hp->maHP
         << setw(28) << hp->tenHP
         << setw(10) << hp->soTinChi
         << fixed << setprecision(2) << setw(10) << hp->diemHe10 << '\n';
}