#include "ThongKe.h"
#include "../QuickSort/QuickSort.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

namespace {
    constexpr int TOP_GIOI_HAN = 10;
    constexpr double NGUONG_CANH_BAO_GPA4 = 1.0;

    struct ThongKeLopItem {
        string tenLop;
        int soLuong = 0;
    };

    void demSoLopKhacNhauDeQuy(AVLNode* node, ThongKeLopItem* dsLop, int& soLopHienTai) {
        if (node == nullptr) {
            return;
        }
        demSoLopKhacNhauDeQuy(node->left, dsLop, soLopHienTai);

        bool daCo = false;
        for (int i = 0; i < soLopHienTai; ++i) {
            if (dsLop[i].tenLop == node->data.lop) {
                daCo = true;
                break;
            }
        }
        if (!daCo) {
            dsLop[soLopHienTai].tenLop = node->data.lop;
            dsLop[soLopHienTai].soLuong = 0;
            ++soLopHienTai;
        }

        demSoLopKhacNhauDeQuy(node->right, dsLop, soLopHienTai);
    }

    void demTheoLopDeQuy(AVLNode* node, ThongKeLopItem* dsLop, int soLop) {
        if (node == nullptr) {
            return;
        }
        demTheoLopDeQuy(node->left, dsLop, soLop);

        for (int i = 0; i < soLop; ++i) {
            if (dsLop[i].tenLop == node->data.lop) {
                ++dsLop[i].soLuong;
                break;
            }
        }

        demTheoLopDeQuy(node->right, dsLop, soLop);
    }

    void demHocLucDeQuy(AVLNode* node,
                        int& xuatSac, int& gioi, int& kha,
                        int& trungBinh, int& yeu, int& chuaCoDiem) {
        if (node == nullptr) {
            return;
        }
        demHocLucDeQuy(node->left, xuatSac, gioi, kha, trungBinh, yeu, chuaCoDiem);

        KetQuaDiem kq = tinhKetQuaHocTap(node->data);
        if (kq.xepLoai == "Xuat sac") ++xuatSac;
        else if (kq.xepLoai == "Gioi") ++gioi;
        else if (kq.xepLoai == "Kha") ++kha;
        else if (kq.xepLoai == "Trung binh") ++trungBinh;
        else if (kq.xepLoai == "Yeu") ++yeu;
        else ++chuaCoDiem;

        demHocLucDeQuy(node->right, xuatSac, gioi, kha, trungBinh, yeu, chuaCoDiem);
    }

    void duyetCanhBaoDeQuy(AVLNode* node, int& dem) {
        if (node == nullptr) {
            return;
        }
        duyetCanhBaoDeQuy(node->left, dem);

        KetQuaDiem kq = tinhKetQuaHocTap(node->data);
        if (kq.tongTinChi > 0 && kq.gpaHe4 < NGUONG_CANH_BAO_GPA4) {
            cout << left << setw(14) << node->data.mssv
                 << setw(25) << node->data.hoTen
                 << setw(14) << node->data.lop
                 << "GPA4: " << fixed << setprecision(2) << kq.gpaHe4
                 << " | GPA10: " << kq.gpaHe10 << '\n';
            ++dem;
        }

        duyetCanhBaoDeQuy(node->right, dem);
    }
}

void thongKeTheoLopAVL(AVLNode* root) {
    cout << "\n--- THONG KE SINH VIEN THEO LOP ---\n";
    if (root == nullptr) {
        cout << "Danh sach sinh vien rong.\n";
        return;
    }

    int tongSV = demSoNutAVL(root);
    if (tongSV <= 0) {
        cout << "Danh sach sinh vien rong.\n";
        return;
    }

    ThongKeLopItem* dsLop = new ThongKeLopItem[tongSV];
    int soLop = 0;
    demSoLopKhacNhauDeQuy(root, dsLop, soLop);
    demTheoLopDeQuy(root, dsLop, soLop);

    for (int i = 0; i < soLop; ++i) {
        cout << "Lop " << dsLop[i].tenLop << ": " << dsLop[i].soLuong << " sinh vien\n";
    }

    delete[] dsLop;
    dsLop = nullptr;
}

void thongKeHocLucAVL(AVLNode* root) {
    cout << "\n--- THONG KE XEP LOAI HOC LUC ---\n";
    if (root == nullptr) {
        cout << "Danh sach sinh vien rong.\n";
        return;
    }

    int xuatSac = 0, gioi = 0, kha = 0, trungBinh = 0, yeu = 0, chuaCoDiem = 0;
    demHocLucDeQuy(root, xuatSac, gioi, kha, trungBinh, yeu, chuaCoDiem);

    cout << "Xuat sac    : " << xuatSac << " sinh vien\n";
    cout << "Gioi        : " << gioi << " sinh vien\n";
    cout << "Kha         : " << kha << " sinh vien\n";
    cout << "Trung binh  : " << trungBinh << " sinh vien\n";
    cout << "Yeu         : " << yeu << " sinh vien\n";
    cout << "Chua co diem: " << chuaCoDiem << " sinh vien\n";
}

void canhBaoHocVuAVL(AVLNode* root) {
    cout << "\n--- DANH SACH CANH BAO HOC VU (GPA HE 4 < 1.0) ---\n";
    if (root == nullptr) {
        cout << "Danh sach sinh vien rong.\n";
        return;
    }

    int dem = 0;
    duyetCanhBaoDeQuy(root, dem);

    if (dem == 0) {
        cout << "Khong co sinh vien bi canh bao hoc vu.\n";
    }
    cout << "Tong so sinh vien canh bao: " << dem << '\n';
}

void top10SinhVienAVL(AVLNode* root, bool uuTienHe4) {
    cout << "\n--- TOP 10 SINH VIEN CO GPA CAO NHAT ---\n";
    if (root == nullptr) {
        cout << "Danh sach sinh vien rong.\n";
        return;
    }

    int soLuong = 0;
    BanGhiXepHangSV* arr = trichXuatTuAVL(root, "", soLuong);
    if (arr == nullptr || soLuong <= 0) {
        cout << "Khong co du lieu sinh vien de xep hang.\n";
        return;
    }

    if (soLuong > 1) {
        quickSortGiamDan(arr, 0, soLuong - 1, uuTienHe4);
    }

    int gioiHan = (soLuong < TOP_GIOI_HAN) ? soLuong : TOP_GIOI_HAN;
    cout << left << setw(6) << "Hang"
         << setw(14) << "MSSV"
         << setw(25) << "Ho ten"
         << setw(14) << "Lop"
         << setw(10) << "GPA4"
         << setw(10) << "GPA10" << '\n';
    cout << string(79, '-') << '\n';

    for (int i = 0; i < gioiHan; ++i) {
        cout << left << setw(6) << (i + 1)
             << setw(14) << arr[i].sv.mssv
             << setw(25) << arr[i].sv.hoTen
             << setw(14) << arr[i].sv.lop
             << fixed << setprecision(2)
             << setw(10) << arr[i].gpaHe4
             << setw(10) << arr[i].gpaHe10 << '\n';
    }

    giaiPhongMangXepHang(arr, soLuong);
}