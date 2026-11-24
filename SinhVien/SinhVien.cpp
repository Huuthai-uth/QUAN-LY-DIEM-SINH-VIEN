#include "SinhVien.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

namespace {
    constexpr int MIN_YEAR = 1950;
    constexpr int MAX_YEAR = 2026;

    bool laNamNhuan(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int soNgayTrongThang(int month, int year) {
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return 31;
            case 4: case 6: case 9: case 11:
                return 30;
            case 2:
                return laNamNhuan(year) ? 29 : 28;
            default:
                return 0;
        }
    }
}

bool kiemTraMSSV(const string& mssv) {
    if (mssv.empty() || mssv.length() > 20) {
        return false;
    }
    for (char c : mssv) {
        if (!isalnum(static_cast<unsigned char>(c)) && c != '_') {
            return false;
        }
    }
    return true;
}

bool kiemTraChuoiKhongRong(const string& str, size_t maxLen) {
    if (str.empty() || str.length() > maxLen) {
        return false;
    }
    for (char c : str) {
        if (!isspace(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

// Dinh dang chuan: dd/mm/yyyy (10 ky tu)
bool kiemTraNgaySinh(const string& ngaySinh) {
    if (ngaySinh.length() != 10 || ngaySinh[2] != '/' || ngaySinh[5] != '/') {
        return false;
    }
    for (int i = 0; i < 10; ++i) {
        if (i != 2 && i != 5 && !isdigit(static_cast<unsigned char>(ngaySinh[i]))) {
            return false;
        }
    }

    int day = stoi(ngaySinh.substr(0, 2));
    int month = stoi(ngaySinh.substr(3, 2));
    int year = stoi(ngaySinh.substr(6, 4));

    if (year < MIN_YEAR || year > MAX_YEAR || month < 1 || month > 12) {
        return false;
    }
    int maxDay = soNgayTrongThang(month, year);
    return day >= 1 && day <= maxDay;
}

bool kiemTraSinhVienHopLe(const SinhVien& sv) {
    return kiemTraMSSV(sv.mssv) &&
           kiemTraChuoiKhongRong(sv.hoTen, 100) &&
           kiemTraChuoiKhongRong(sv.lop, 40) &&
           kiemTraNgaySinh(sv.ngaySinh);
}

SinhVien taoSinhVien(const string& mssv, const string& hoTen,
                     const string& lop, const string& ngaySinh) {
    SinhVien sv;
    sv.mssv = mssv;
    sv.hoTen = hoTen;
    sv.lop = lop;
    sv.ngaySinh = ngaySinh;
    sv.dsHocPhan = nullptr;
    return sv;
}

SinhVien nhapSinhVien() {
    string mssv, hoTen, lop, ngaySinh;

    while (true) {
        cout << "Nhap MSSV: ";
        getline(cin >> ws, mssv);
        if (kiemTraMSSV(mssv)) {
            break;
        }
        cout << "MSSV khong hop le! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap ho ten: ";
        getline(cin >> ws, hoTen);
        if (kiemTraChuoiKhongRong(hoTen, 100)) {
            break;
        }
        cout << "Ho ten khong hop le hoac de trong!\n";
    }

    while (true) {
        cout << "Nhap lop: ";
        getline(cin >> ws, lop);
        if (kiemTraChuoiKhongRong(lop, 40)) {
            break;
        }
        cout << "Lop khong hop le hoac de trong!\n";
    }

    while (true) {
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin >> ws, ngaySinh);
        if (kiemTraNgaySinh(ngaySinh)) {
            break;
        }
        cout << "Ngay sinh khong hop le! Dinh dang dung: dd/mm/yyyy.\n";
    }

    return taoSinhVien(mssv, hoTen, lop, ngaySinh);
}

void xuatSinhVien(const SinhVien& sv) {
    cout << left << setw(14) << sv.mssv
         << setw(26) << sv.hoTen
         << setw(14) << sv.lop
         << setw(14) << sv.ngaySinh
         << "So HP: " << demSoHocPhan(sv.dsHocPhan) << '\n';
}

void giaiPhongSinhVien(SinhVien& sv) {
    giaiPhongDSLK(sv.dsHocPhan);
    sv.dsHocPhan = nullptr;
}