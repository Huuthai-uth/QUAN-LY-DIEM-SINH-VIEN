#include "QuanLyDiem.h"
#include <iostream>
#include <iomanip>

using namespace std;

double quyDoiDiemHe4(float diem10) {
    if (!kiemTraDiem(diem10)) {
        return 0.0;
    }
    if (diem10 >= 8.5f) return 4.0;
    if (diem10 >= 8.0f) return 3.5;
    if (diem10 >= 7.0f) return 3.0;
    if (diem10 >= 6.5f) return 2.5;
    if (diem10 >= 5.5f) return 2.0;
    if (diem10 >= 5.0f) return 1.5;
    if (diem10 >= 4.0f) return 1.0;
    return 0.0;
}

string xepLoaiHocLuc(double gpa10) {
    if (gpa10 >= 8.5) return "Xuat sac";
    if (gpa10 >= 7.0) return "Gioi";
    if (gpa10 >= 5.5) return "Kha";
    if (gpa10 >= 4.0) return "Trung binh";
    return "Yeu";
}

KetQuaDiem tinhKetQuaHocTap(const SinhVien& sv) {
    KetQuaDiem kq;
    double tongDiem10 = 0.0;
    double tongDiem4 = 0.0;
    int tongTC = 0;

    const HocPhan* cur = sv.dsHocPhan;
    while (cur != nullptr) {
        if (kiemTraSoTinChi(cur->soTinChi) && kiemTraDiem(cur->diemHe10)) {
            tongDiem10 += static_cast<double>(cur->diemHe10) * cur->soTinChi;
            tongDiem4 += quyDoiDiemHe4(cur->diemHe10) * cur->soTinChi;
            tongTC += cur->soTinChi;
        }
        cur = cur->next;
    }

    kq.tongTinChi = tongTC;
    if (tongTC == 0) {
        kq.gpaHe10 = 0.0;
        kq.gpaHe4 = 0.0;
        kq.xepLoai = "Chua co diem";
        return kq;
    }

    kq.gpaHe10 = tongDiem10 / tongTC;
    kq.gpaHe4 = tongDiem4 / tongTC;
    kq.xepLoai = xepLoaiHocLuc(kq.gpaHe10);
    return kq;
}

void inBangDiemSinhVien(const SinhVien& sv) {
    cout << "\n==================== BANG DIEM SINH VIEN ====================\n";
    cout << "MSSV     : " << sv.mssv << '\n';
    cout << "Ho ten   : " << sv.hoTen << '\n';
    cout << "Lop      : " << sv.lop << '\n';
    cout << "Ngay sinh: " << sv.ngaySinh << '\n';
    cout << "-------------------------------------------------------------\n";

    xuatDanhSachHocPhan(sv.dsHocPhan);

    KetQuaDiem kq = tinhKetQuaHocTap(sv);
    cout << "-------------------------------------------------------------\n";
    cout << "Tong tin chi : " << kq.tongTinChi << '\n';
    cout << fixed << setprecision(2);
    cout << "GPA he 10    : " << kq.gpaHe10 << '\n';
    cout << "GPA he 4     : " << kq.gpaHe4 << '\n';
    cout << "Xep loai     : " << kq.xepLoai << '\n';
    cout << "=============================================================\n";
}

bool themHocPhanChoSinhVien(SinhVien& sv, const string& maHP, const string& tenHP,
                           int soTinChi, float diemHe10) {
    HocPhan* hpMoi = taoHocPhan(maHP, tenHP, soTinChi, diemHe10);
    if (hpMoi == nullptr) {
        return false;
    }
    themHocPhan(sv.dsHocPhan, hpMoi);
    return true;
}

bool suaDiemChoSinhVien(SinhVien& sv, const string& maHP, float diemMoi) {
    return suaDiemHocPhan(sv.dsHocPhan, maHP, diemMoi);
}