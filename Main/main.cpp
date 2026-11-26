#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
#include <string>

#include "../SinhVien/SinhVien.h"
#include "../HocPhan/HocPhan.h"
#include "../LinkedList/LinkedList.h"
#include "../AVL/AVL.h"
#include "../BST/BST.h"
#include "../FileManager/FileManager.h"
#include "../QuanLyDiem/QuanLyDiem.h"
#include "../QuickSort/QuickSort.h"
#include "../ThongKe/ThongKe.h"

using namespace std;

namespace {
    int maxInt(int a, int b) {
        return (a > b) ? a : b;
    }

    void xoaBoDemNhap() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int nhapSoNguyenAnToan(const string& loiChao) {
        int val = 0;
        while (true) {
            cout << loiChao;
            if (cin >> val) {
                xoaBoDemNhap();
                return val;
            }
            cout << "Gia tri khong hop le! Vui long nhap so nguyen.\n";
            xoaBoDemNhap();
        }
    }

    int nhapTinChiAnToan(const string& loiChao) {
        int tc = 0;
        while (true) {
            cout << loiChao;
            if (cin >> tc && kiemTraSoTinChi(tc)) {
                xoaBoDemNhap();
                return tc;
            }
            cout << "So tin chi khong hop le! Vui long nhap lai.\n";
            xoaBoDemNhap();
        }
    }

    float nhapDiemAnToan(const string& loiChao) {
        float diem = 0.0f;
        while (true) {
            cout << loiChao;
            if (cin >> diem && kiemTraDiem(diem)) {
                xoaBoDemNhap();
                return diem;
            }
            cout << "Diem khong hop le! Vui long nhap trong khoang 0.0 - 10.0.\n";
            xoaBoDemNhap();
        }
    }

    void sapXepVaInDanhSachLop(AVLNode* rootAVL) {
        if (rootAVL == nullptr) {
            cout << "Cay AVL dang rong.\n";
            return;
        }

        string tenLop;
        cout << "Nhap ten lop can sap xep giam dan theo GPA: ";
        getline(cin >> ws, tenLop);

        cout << "Chon thang diem sap xep (1: GPA he 10, 2: GPA he 4): ";
        int chonThang = nhapSoNguyenAnToan("");
        bool uuTienHe4 = (chonThang == 2);

        int soLuong = 0;
        BanGhiXepHangSV* dsLop = sapXepLopGiamDanAVL(rootAVL, tenLop, soLuong, uuTienHe4);
        if (dsLop == nullptr || soLuong <= 0) {
            cout << "Khong tim thay sinh vien nao thuoc lop \"" << tenLop << "\".\n";
            return;
        }

        cout << "\n--- DANH SACH LOP " << tenLop
             << " SAP XEP GIAM DAN THEO " << (uuTienHe4 ? "GPA HE 4" : "GPA HE 10") << " ---\n";
        cout << left << setw(6) << "STT"
             << setw(14) << "MSSV"
             << setw(25) << "Ho ten"
             << setw(14) << "Lop"
             << setw(10) << "GPA4"
             << setw(10) << "GPA10" << '\n';
        cout << string(79, '-') << '\n';

        for (int i = 0; i < soLuong; ++i) {
            cout << left << setw(6) << (i + 1)
                 << setw(14) << dsLop[i].sv.mssv
                 << setw(25) << dsLop[i].sv.hoTen
                 << setw(14) << dsLop[i].sv.lop
                 << fixed << setprecision(2)
                 << setw(10) << dsLop[i].gpaHe4
                 << setw(10) << dsLop[i].gpaHe10 << '\n';
        }

        giaiPhongMangXepHang(dsLop, soLuong);
    }

    void soSanhBSTVaAVL_TangDan(int soLuong) {
        if (soLuong <= 0) {
            cout << "So luong phai lon hon 0.\n";
            return;
        }

        BSTNode* rootBST = nullptr;
        AVLNode* rootAVL = nullptr;

        auto batDauBST = chrono::high_resolution_clock::now();
        for (int i = 1; i <= soLuong; ++i) {
            string numStr = to_string(i);
            int soZero = maxInt(0, 6 - static_cast<int>(numStr.size()));
            string mssv = "SV" + string(soZero, '0') + numStr;
            SinhVien sv = taoSinhVien(mssv, "Sinh Vien " + numStr, "CNTT01", "01/01/2005");
            bool ok = false;
            rootBST = insertBST(rootBST, sv, ok);
            giaiPhongSinhVien(sv);
        }
        auto ketThucBST = chrono::high_resolution_clock::now();

        auto batDauAVL = chrono::high_resolution_clock::now();
        for (int i = 1; i <= soLuong; ++i) {
            string numStr = to_string(i);
            int soZero = maxInt(0, 6 - static_cast<int>(numStr.size()));
            string mssv = "SV" + string(soZero, '0') + numStr;
            SinhVien sv = taoSinhVien(mssv, "Sinh Vien " + numStr, "CNTT01", "01/01/2005");
            bool ok = false;
            rootAVL = insertAVL(rootAVL, sv, ok);
            giaiPhongSinhVien(sv);
        }
        auto ketThucAVL = chrono::high_resolution_clock::now();

        double msBST = chrono::duration<double, milli>(ketThucBST - batDauBST).count();
        double msAVL = chrono::duration<double, milli>(ketThucAVL - batDauAVL).count();

        cout << "\n--- SO SANH BST THUONG VA AVL (MSSV TANG DAN, N = " << soLuong << ") ---\n";
        cout << "Chieu cao BST : " << getHeightBST(rootBST)
             << " | Thoi gian chen: " << fixed << setprecision(3) << msBST << " ms\n";
        cout << "Chieu cao AVL : " << getHeight(rootAVL)
             << " | Thoi gian chen: " << fixed << setprecision(3) << msAVL << " ms\n";

        giaiPhongBST(rootBST);
        giaiPhongAVL(rootAVL);
    }

    void inMenu() {
        cout << "\n================ QUAN LY DIEM SINH VIEN (AVL) ================\n";
        cout << "1. Nap lai du lieu tu file SinhVien & HocPhan\n";
        cout << "2. Them sinh vien moi (AVL)\n";
        cout << "3. Xoa sinh vien theo MSSV (AVL)\n";
        cout << "4. Tim kiem sinh vien & xem bang diem\n";
        cout << "5. Them / Sua diem hoc phan cho sinh vien\n";
        cout << "6. In danh sach sinh vien theo MSSV (Duyet LNR)\n";
        cout << "7. Sap xep danh sach mot lop giam dan theo GPA (Quick Sort)\n";
        cout << "8. Thong ke (Theo lop / Hoc luc / Canh bao hoc vu / Top 10)\n";
        cout << "9. Hien thi cay AVL kem he so can bang\n";
        cout << "10. So sanh BST vs AVL (MSSV tang dan)\n";
        cout << "11. Thuc nghiem du lieu lon ngau nhien (>= 10^4 ban ghi) & do thoi gian\n";
        cout << "12. Ghi du lieu ra file va thoat\n";
        cout << "==============================================================\n";
    }
}

int main() {
    AVLNode* rootAVL = nullptr;
    string fileSV = "Data/SinhVien.txt";
    string fileHP = "Data/HocPhan.txt";

    KetQuaFile kqKhoiDong = napDuLieuTongHopAVL(fileSV, fileHP, rootAVL);
    cout << (kqKhoiDong.thanhCong ? "[OK] " : "[LOI] ") << kqKhoiDong.thongBao << '\n';

    while (true) {
        inMenu();
        int chon = nhapSoNguyenAnToan("Nhap lua chon: ");

        if (chon == 1) {
            cout << "Nhap duong dan file sinh vien (mac dinh: " << fileSV << "): ";
            string inpSV;
            getline(cin, inpSV);
            if (!inpSV.empty()) fileSV = inpSV;

            cout << "Nhap duong dan file hoc phan (mac dinh: " << fileHP << "): ";
            string inpHP;
            getline(cin, inpHP);
            if (!inpHP.empty()) fileHP = inpHP;

            giaiPhongAVL(rootAVL);
            KetQuaFile kq = napDuLieuTongHopAVL(fileSV, fileHP, rootAVL);
            cout << (kq.thanhCong ? "[OK] " : "[LOI] ") << kq.thongBao << '\n';
        } else if (chon == 2) {
            SinhVien sv = nhapSinhVien();
            int soHP = nhapSoNguyenAnToan("Nhap so luong hoc phan ban dau: ");
            if (soHP < 0) soHP = 0;

            for (int i = 0; i < soHP; ++i) {
                cout << "--- Hoc phan " << (i + 1) << " ---\n";
                HocPhan* hp = nhapHocPhan();
                themHocPhan(sv.dsHocPhan, hp);
            }

            bool ok = false;
            rootAVL = insertAVL(rootAVL, sv, ok);
            giaiPhongSinhVien(sv);
            cout << (ok ? "Them sinh vien thanh cong!\n"
                        : "Them sinh vien that bai (trung MSSV hoac du lieu khong hop le)!\n");
        } else if (chon == 3) {
            string mssv;
            cout << "Nhap MSSV can xoa: ";
            getline(cin >> ws, mssv);
            bool ok = false;
            rootAVL = removeAVL(rootAVL, mssv, ok);
            cout << (ok ? "Da xoa sinh vien!\n" : "Khong tim thay MSSV can xoa!\n");
        } else if (chon == 4) {
            string mssv;
            cout << "Nhap MSSV can tim: ";
            getline(cin >> ws, mssv);
            AVLNode* node = searchAVL(rootAVL, mssv);
            if (node != nullptr) {
                inBangDiemSinhVien(node->data);
            } else {
                cout << "Khong tim thay sinh vien co MSSV: " << mssv << '\n';
            }
        } else if (chon == 5) {
            string mssv;
            cout << "Nhap MSSV: ";
            getline(cin >> ws, mssv);
            AVLNode* node = searchAVL(rootAVL, mssv);
            if (node == nullptr) {
                cout << "Khong tim thay sinh vien!\n";
            } else {
                cout << "1. Them hoc phan\n2. Sua diem hoc phan\n";
                int sub = nhapSoNguyenAnToan("Chon: ");
                if (sub == 1) {
                    string maHP, tenHP;
                    cout << "Nhap ma hoc phan: ";
                    getline(cin >> ws, maHP);
                    cout << "Nhap ten hoc phan: ";
                    getline(cin >> ws, tenHP);
                    int tc = nhapTinChiAnToan("Nhap so tin chi: ");
                    float diem = nhapDiemAnToan("Nhap diem he 10 (0.0 - 10.0): ");
                    cout << (themHocPhanChoSinhVien(node->data, maHP, tenHP, tc, diem)
                                 ? "Da them hoc phan thanh cong!\n"
                                 : "Them hoc phan that bai (du lieu khong hop le)!\n");
                } else if (sub == 2) {
                    string maHP;
                    cout << "Nhap ma hoc phan can sua diem: ";
                    getline(cin >> ws, maHP);
                    float diemMoi = nhapDiemAnToan("Nhap diem moi (0.0 - 10.0): ");
                    cout << (suaDiemChoSinhVien(node->data, maHP, diemMoi)
                                 ? "Cap nhat diem thanh cong!\n"
                                 : "Sua diem that bai (ma HP khong ton tai hoac diem khong hop le)!\n");
                } else {
                    cout << "Lua chon khong hop le.\n";
                }
            }
        } else if (chon == 6) {
            if (rootAVL == nullptr) {
                cout << "Cay AVL dang rong.\n";
            } else {
                cout << "\n--- DANH SACH SINH VIEN THEO MSSV (LNR) ---\n";
                duyetLNR_AVL(rootAVL);
            }
        } else if (chon == 7) {
            sapXepVaInDanhSachLop(rootAVL);
        } else if (chon == 8) {
            thongKeTheoLopAVL(rootAVL);
            thongKeHocLucAVL(rootAVL);
            canhBaoHocVuAVL(rootAVL);
            top10SinhVienAVL(rootAVL, false);
        } else if (chon == 9) {
            if (rootAVL == nullptr) {
                cout << "Cay AVL dang rong.\n";
            } else {
                cout << "\n--- CAY AVL KEM HE SO CAN BANG ---\n";
                inCayAVL_KemCanBang(rootAVL);
            }
        } else if (chon == 10) {
            int n = nhapSoNguyenAnToan("Nhap so luong MSSV tang dan de so sanh: ");
            soSanhBSTVaAVL_TangDan(n);
        } else if (chon == 11) {
            int n = nhapSoNguyenAnToan("Nhap so luong ban ghi ngau nhien (>= 10000): ");
            thucNghiemAVLvaBST(n, false, "Data/SinhVien_NgauNhien.txt");
        } else if (chon == 12) {
            KetQuaFile kqGhi = ghiDuLieuRaFileAVL(rootAVL, fileSV, fileHP);
            cout << (kqGhi.thanhCong ? "[OK] " : "[LOI] ") << kqGhi.thongBao << '\n';
            giaiPhongAVL(rootAVL);
            cout << "Da giai phong bo nho va thoat chuong trinh.\n";
            break;
        } else {
            cout << "Lua chon khong nam trong menu (1 - 12)!\n";
        }
    }

    return 0;
}