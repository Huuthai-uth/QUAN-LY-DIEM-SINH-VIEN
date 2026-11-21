#include "ThongKe.h"
#include "QuickSort.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

static void taoBanSaoDaTinhGPA(const DanhSachSV& nguon, DanhSachSV& dich) {
    khoiTaoDanhSach(dich, nguon.size > 0 ? nguon.size : 1);
    for (int i = 0; i < nguon.size; ++i) {
        themVaoDanhSach(dich, nguon.data[i]);
        capNhatGPA(dich.data[i]);
    }
}

void thongKeTheoLop(const DanhSachSV& ds) {
    cout << "\n--- THONG KE SINH VIEN THEO LOP ---\n";
    if (ds.size == 0) {
        cout << "Danh sach sinh vien rong.\n";
        return;
    }

    string* tenLop = new string[ds.size];
    int* soLuong = new int[ds.size];
    int soLop = 0;

    for (int i = 0; i < ds.size; ++i) {
        int idx = -1;
        for (int j = 0; j < soLop; ++j) {
            if (tenLop[j] == ds.data[i].lop) {
                idx = j;
                break;
            }
        }
        if (idx != -1) {
            ++soLuong[idx];
        } else {
            tenLop[soLop] = ds.data[i].lop;
            soLuong[soLop] = 1;
            ++soLop;
        }
    }

    for (int i = 0; i < soLop; ++i) {
        cout << "Lop " << tenLop[i] << ": " << soLuong[i] << " sinh vien\n";
    }

    delete[] tenLop;
    delete[] soLuong;
}

void thongKeHocLuc(const DanhSachSV& ds) {
    const string muc[5] = {"Xuat sac", "Gioi", "Kha", "Trung binh", "Yeu"};
    int dem[5] = {0, 0, 0, 0, 0};

    DanhSachSV tam;
    taoBanSaoDaTinhGPA(ds, tam);

    for (int i = 0; i < tam.size; ++i) {
        string xl = xepLoaiHocLuc(tam.data[i].gpa10);
        for (int m = 0; m < 5; ++m) {
            if (muc[m] == xl) {
                ++dem[m];
                break;
            }
        }
    }

    cout << "\n--- THONG KE HOC LUC ---\n";
    for (int m = 0; m < 5; ++m) {
        cout << muc[m] << ": " << dem[m] << " sinh vien\n";
    }

    giaiPhongDanhSach(tam);
}

void canhBaoHocVu(const DanhSachSV& ds) {
    DanhSachSV tam;
    taoBanSaoDaTinhGPA(ds, tam);

    cout << "\n--- DANH SACH CANH BAO HOC VU (GPA HE 4 < 1.0) ---\n";
    int dem = 0;
    for (int i = 0; i < tam.size; ++i) {
        if (tam.data[i].gpa4 < 1.0) {
            cout << tam.data[i].maSV << " | " << tam.data[i].hoTen << " | " << tam.data[i].lop
                 << " | GPA4: " << fixed << setprecision(2) << tam.data[i].gpa4 << "\n";
            ++dem;
        }
    }
    if (dem == 0) cout << "Khong co sinh vien bi canh bao.\n";
    cout << "Tong so sinh vien canh bao: " << dem << "\n";

    giaiPhongDanhSach(tam);
}

void top10SinhVien(const DanhSachSV& ds) {
    DanhSachSV tam;
    taoBanSaoDaTinhGPA(ds, tam);
    sapXepGiamDan(tam);

    cout << "\n--- TOP 10 SINH VIEN CO GPA HE 4 CAO NHAT ---\n";
    if (tam.size == 0) {
        cout << "Danh sach sinh vien rong.\n";
        giaiPhongDanhSach(tam);
        return;
    }

    int soLuong = tam.size < 10 ? tam.size : 10;
    cout << left << setw(5) << "Hang" << setw(14) << "Ma SV"
         << setw(25) << "Ho ten" << setw(14) << "Lop"
         << setw(10) << "GPA4" << "GPA10\n";
    for (int i = 0; i < soLuong; ++i) {
        cout << left << setw(5) << i + 1 << setw(14) << tam.data[i].maSV
             << setw(25) << tam.data[i].hoTen << setw(14) << tam.data[i].lop
             << fixed << setprecision(2) << setw(10) << tam.data[i].gpa4
             << tam.data[i].gpa10 << "\n";
    }

    giaiPhongDanhSach(tam);
}
