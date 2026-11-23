#include "HocPhan.h"
#include <iostream>
#include <iomanip>
#include <cctype>

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

bool kiemTraSoTinChi(int soTinChi) {
    return soTinChi > 0 && soTinChi <= 15;
}

bool kiemTraDiem(float diem) {
    return diem >= 0.0f && diem <= 10.0f;
}

HocPhan* taoHocPhan(const string& maHP, int soTinChi, float diemHe10) {
    if (!kiemTraMaHP(maHP) || !kiemTraSoTinChi(soTinChi) || !kiemTraDiem(diemHe10)) {
        return nullptr;
    }
    HocPhan* hp = new HocPhan;
    hp->maHP = maHP;
    hp->soTinChi = soTinChi;
    hp->diemHe10 = diemHe10;
    hp->next = nullptr;
    return hp;
}

HocPhan* nhapHocPhan() {
    string maHP;
    int soTinChi;
    float diemHe10;

    while (true) {
        cout << "Nhap ma hoc phan: ";
        getline(cin >> ws, maHP);
        if (kiemTraMaHP(maHP)) {
            break;
        }
        cout << "Ma hoc phan khong hop le! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap so tin chi (1 - 15): ";
        if (cin >> soTinChi && kiemTraSoTinChi(soTinChi)) {
            break;
        }
        cout << "So tin chi khong hop le! Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    while (true) {
        cout << "Nhap diem he 10 (0.0 - 10.0): ";
        if (cin >> diemHe10 && kiemTraDiem(diemHe10)) {
            cin.ignore(10000, '\n');
            break;
        }
        cout << "Diem khong hop le! Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return taoHocPhan(maHP, soTinChi, diemHe10);
}

void xuatHocPhan(const HocPhan* hp) {
    if (hp == nullptr) {
        return;
    }
    cout << left << setw(14) << hp->maHP
         << setw(10) << hp->soTinChi
         << fixed << setprecision(2) << setw(10) << hp->diemHe10 << '\n';
}