#include "HocPhan.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>

using namespace std;

namespace {
    string trim(const string& s) {
        size_t start = 0;
        while (start < s.length() && isspace(static_cast<unsigned char>(s[start]))) {
            ++start;
        }
        size_t end = s.length();
        while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
            --end;
        }
        return s.substr(start, end - start);
    }

    // Ep kieu so nguyen nghiem ngat: chan "3.5", "3abc", chuoi rong, tran so
    bool parseIntStrict(const string& input, int& outVal) {
        string s = trim(input);
        if (s.empty()) {
            return false;
        }
        try {
            size_t pos = 0;
            int val = stoi(s, &pos);
            if (pos != s.length()) {
                return false;
            }
            outVal = val;
            return true;
        } catch (...) {
            return false;
        }
    }

    // Ep kieu so thuc nghiem ngat: chan "8.5abc", "8,5", "nan", "inf"
    bool parseFloatStrict(const string& input, float& outVal) {
        string s = trim(input);
        if (s.empty()) {
            return false;
        }
        try {
            size_t pos = 0;
            float val = stof(s, &pos);
            if (pos != s.length() || !isfinite(val)) {
                return false;
            }
            outVal = val;
            return true;
        } catch (...) {
            return false;
        }
    }
}

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
        if (c == '|' || c == '\r' || c == '\n') {
            return false; // Tranh lam hong dinh dang file khi ghi/doc
        }
        if (!isspace(static_cast<unsigned char>(c))) {
            coKyTuKhongRong = true;
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
    string maSach = trim(maHP);
    string tenSach = trim(tenHP);

    if (!kiemTraMaHP(maSach) || !kiemTraTenHP(tenSach) ||
        !kiemTraSoTinChi(soTinChi) || !kiemTraDiem(diemHe10)) {
        return nullptr;
    }

    HocPhan* hp = new HocPhan;
    hp->maHP = maSach;
    hp->tenHP = tenSach;
    hp->soTinChi = soTinChi;
    hp->diemHe10 = diemHe10;
    hp->next = nullptr;
    return hp;
}

HocPhan* nhapHocPhan() {
    string line;
    string maHP;
    string tenHP;
    int soTinChi = 0;
    float diemHe10 = 0.0f;

    while (true) {
        cout << "Nhap ma hoc phan: ";
        if (!getline(cin, line)) {
            return nullptr;
        }
        maHP = trim(line);
        if (kiemTraMaHP(maHP)) {
            break;
        }
        cout << "Ma hoc phan khong hop le (chi gom chu, so, '_', '-', toi da 20 ky tu)! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap ten hoc phan: ";
        if (!getline(cin, line)) {
            return nullptr;
        }
        tenHP = trim(line);
        if (kiemTraTenHP(tenHP)) {
            break;
        }
        cout << "Ten hoc phan khong hop le (khong rong, khong chua '|', toi da 100 ky tu)! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap so tin chi (1 - 15): ";
        if (!getline(cin, line)) {
            return nullptr;
        }
        if (parseIntStrict(line, soTinChi) && kiemTraSoTinChi(soTinChi)) {
            break;
        }
        cout << "So tin chi khong hop le (phai la so nguyen tu 1 den 15)! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap diem he 10 (0.0 - 10.0): ";
        if (!getline(cin, line)) {
            return nullptr;
        }
        if (parseFloatStrict(line, diemHe10) && kiemTraDiem(diemHe10)) {
            break;
        }
        cout << "Diem khong hop le (phai la so thuc tu 0.0 den 10.0)! Vui long nhap lai.\n";
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