#include "QuanLyDiem.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

void themMonVaoSV(SinhVien& sv, const MonHoc& mh) {
    NodeMonHoc* newNode = new NodeMonHoc;
    newNode->data = mh;
    newNode->next = nullptr;

    if (sv.headMonHoc == nullptr) {
        sv.headMonHoc = newNode;
    } else {
        NodeMonHoc* cur = sv.headMonHoc;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
    ++sv.soMonHoc;
}

bool xoaMonKhoiSV(SinhVien& sv, const string& maHP) {
    NodeMonHoc* cur = sv.headMonHoc;
    NodeMonHoc* prev = nullptr;

    while (cur != nullptr && cur->data.maHP != maHP) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == nullptr) return false;

    if (prev == nullptr) {
        sv.headMonHoc = cur->next;
    } else {
        prev->next = cur->next;
    }
    delete cur;
    --sv.soMonHoc;
    return true;
}

void saoChepSinhVien(SinhVien& dich, const SinhVien& nguon) {
    if (&dich == &nguon) return;
    giaiPhongSinhVien(dich);
    dich.maSV = nguon.maSV;
    dich.hoTen = nguon.hoTen;
    dich.lop = nguon.lop;
    dich.ngaySinh = nguon.ngaySinh;
    dich.gpa10 = nguon.gpa10;
    dich.gpa4 = nguon.gpa4;

    NodeMonHoc* cur = nguon.headMonHoc;
    while (cur != nullptr) {
        themMonVaoSV(dich, cur->data);
        cur = cur->next;
    }
}

void giaiPhongSinhVien(SinhVien& sv) {
    NodeMonHoc* cur = sv.headMonHoc;
    while (cur != nullptr) {
        NodeMonHoc* temp = cur->next;
        delete cur;
        cur = temp;
    }
    sv.headMonHoc = nullptr;
    sv.soMonHoc = 0;
}

void khoiTaoDanhSach(DanhSachSV& ds, int initCap) {
    giaiPhongDanhSach(ds);
    ds.capacity = (initCap > 0) ? initCap : 4;
    ds.data = new SinhVien[ds.capacity];
    ds.size = 0;
}

void giaiPhongDanhSach(DanhSachSV& ds) {
    if (ds.data != nullptr) {
        for (int i = 0; i < ds.size; ++i) {
            giaiPhongSinhVien(ds.data[i]);
        }
        delete[] ds.data;
        ds.data = nullptr;
    }
    ds.size = 0;
    ds.capacity = 0;
}

void themVaoDanhSach(DanhSachSV& ds, const SinhVien& sv) {
    if (ds.data == nullptr) {
        khoiTaoDanhSach(ds, 4);
    }
    if (ds.size >= ds.capacity) {
        int newCap = ds.capacity * 2;
        SinhVien* newArr = new SinhVien[newCap];
        for (int i = 0; i < ds.size; ++i) {
            saoChepSinhVien(newArr[i], ds.data[i]);
            giaiPhongSinhVien(ds.data[i]);
        }
        delete[] ds.data;
        ds.data = newArr;
        ds.capacity = newCap;
    }
    saoChepSinhVien(ds.data[ds.size], sv);
    ++ds.size;
}

bool xoaKhoiDanhSach(DanhSachSV& ds, int index) {
    if (index < 0 || index >= ds.size) return false;
    giaiPhongSinhVien(ds.data[index]);
    for (int i = index; i < ds.size - 1; ++i) {
        ds.data[i].maSV = ds.data[i + 1].maSV;
        ds.data[i].hoTen = ds.data[i + 1].hoTen;
        ds.data[i].lop = ds.data[i + 1].lop;
        ds.data[i].ngaySinh = ds.data[i + 1].ngaySinh;
        ds.data[i].headMonHoc = ds.data[i + 1].headMonHoc;
        ds.data[i].soMonHoc = ds.data[i + 1].soMonHoc;
        ds.data[i].gpa10 = ds.data[i + 1].gpa10;
        ds.data[i].gpa4 = ds.data[i + 1].gpa4;

        ds.data[i + 1].headMonHoc = nullptr;
        ds.data[i + 1].soMonHoc = 0;
    }
    --ds.size;
    return true;
}

string toLowerStr(const string& s) {
    string res = s;
    for (size_t i = 0; i < res.size(); ++i) {
        res[i] = static_cast<char>(tolower(static_cast<unsigned char>(res[i])));
    }
    return res;
}

int timViTriSV(const DanhSachSV& ds, const string& maSV) {
    for (int i = 0; i < ds.size; ++i) {
        if (ds.data[i].maSV == maSV) return i;
    }
    return -1;
}

void themSinhVien(DanhSachSV& ds) {
    SinhVien sv;
    cout << "\n--- THEM SINH VIEN ---\n";
    cout << "Nhap MSSV: ";
    getline(cin, sv.maSV);
    if (sv.maSV.empty()) {
        cout << "MSSV khong duoc de trong!\n";
        return;
    }
    if (timViTriSV(ds, sv.maSV) != -1) {
        cout << "MSSV " << sv.maSV << " da ton tai!\n";
        return;
    }
    cout << "Nhap ho ten: ";
    getline(cin, sv.hoTen);
    cout << "Nhap lop: ";
    getline(cin, sv.lop);
    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    getline(cin, sv.ngaySinh);

    themVaoDanhSach(ds, sv);
    giaiPhongSinhVien(sv);
    cout << "Them sinh vien thanh cong!\n";
}

void xoaSinhVien(DanhSachSV& ds) {
    if (ds.size == 0) {
        cout << "\nDanh sach sinh vien rong!\n";
        return;
    }
    string ma;
    cout << "\n--- XOA SINH VIEN ---\n";
    cout << "Nhap MSSV can xoa: ";
    getline(cin, ma);

    int idx = timViTriSV(ds, ma);
    if (idx == -1) {
        cout << "Khong tim thay sinh vien co MSSV " << ma << ".\n";
        return;
    }
    xoaKhoiDanhSach(ds, idx);
    cout << "Da xoa sinh vien " << ma << " thanh cong!\n";
}

void timKiemSinhVien(const DanhSachSV& ds) {
    if (ds.size == 0) {
        cout << "\nDanh sach sinh vien rong!\n";
        return;
    }
    string tuKhoa;
    cout << "\n--- TIM KIEM SINH VIEN ---\n";
    cout << "Nhap MSSV hoac ten can tim: ";
    getline(cin, tuKhoa);
    string keyLower = toLowerStr(tuKhoa);

    bool found = false;
    for (int i = 0; i < ds.size; ++i) {
        if (toLowerStr(ds.data[i].maSV).find(keyLower) != string::npos ||
            toLowerStr(ds.data[i].hoTen).find(keyLower) != string::npos) {
            SinhVien tam;
            saoChepSinhVien(tam, ds.data[i]);
            capNhatGPA(tam);
            cout << "MSSV: " << tam.maSV
                 << " | Ho ten: " << tam.hoTen
                 << " | Lop: " << tam.lop
                 << " | Ngay sinh: " << tam.ngaySinh
                 << " | GPA he 10: " << tam.gpa10 << "\n";
            giaiPhongSinhVien(tam);
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay sinh vien phu hop voi \"" << tuKhoa << "\".\n";
    }
}

void quanLyHocPhan(DanhSachSV& ds) {
    if (ds.size == 0) {
        cout << "\nDanh sach sinh vien rong!\n";
        return;
    }
    string ma;
    cout << "\n--- QUAN LY HOC PHAN ---\n";
    cout << "Nhap MSSV: ";
    getline(cin, ma);

    int idx = timViTriSV(ds, ma);
    if (idx == -1) {
        cout << "Khong tim thay sinh vien " << ma << ".\n";
        return;
    }

    int chon;
    cout << "1. Them hoc phan\n2. Xoa hoc phan\nChon: ";
    cin >> chon;
    cin.ignore(10000, '\n');

    SinhVien& sv = ds.data[idx];
    if (chon == 1) {
        MonHoc mh;
        cout << "Nhap ma hoc phan: ";
        getline(cin, mh.maHP);
        cout << "Nhap ten hoc phan: ";
        getline(cin, mh.tenHP);
        cout << "Nhap so tin chi: ";
        cin >> mh.soTinChi;
        cout << "Nhap diem ban dau (0 - 10): ";
        cin >> mh.diem;
        cin.ignore(10000, '\n');

        if (mh.soTinChi <= 0 || mh.diem < 0.0 || mh.diem > 10.0) {
            cout << "Du lieu tin chi hoac diem khong hop le!\n";
            return;
        }
        themMonVaoSV(sv, mh);
        capNhatGPA(sv);
        cout << "Da them hoc phan thanh cong!\n";
    } else if (chon == 2) {
        string maHP;
        cout << "Nhap ma hoc phan can xoa: ";
        getline(cin, maHP);
        if (!xoaMonKhoiSV(sv, maHP)) {
            cout << "Khong tim thay hoc phan " << maHP << ".\n";
        } else {
            capNhatGPA(sv);
            cout << "Da xoa hoc phan " << maHP << "!\n";
        }
    } else {
        cout << "Lua chon khong hop le.\n";
    }
}

void nhapVaSuaDiem(DanhSachSV& ds) {
    if (ds.size == 0) {
        cout << "\nDanh sach sinh vien rong!\n";
        return;
    }
    string ma;
    cout << "\n--- NHAP VA SUA DIEM ---\n";
    cout << "Nhap MSSV: ";
    getline(cin, ma);

    int idx = timViTriSV(ds, ma);
    if (idx == -1) {
        cout << "Khong tim thay sinh vien " << ma << ".\n";
        return;
    }

    SinhVien& sv = ds.data[idx];
    if (sv.headMonHoc == nullptr) {
        cout << "Sinh vien chua co hoc phan nao. Hay them hoc phan o muc 4 truoc.\n";
        return;
    }

    cout << "Danh sach hoc phan cua " << sv.hoTen << ":\n";
    int stt = 1;
    NodeMonHoc* cur = sv.headMonHoc;
    while (cur != nullptr) {
        cout << stt++ << ". [" << cur->data.maHP << "] "
             << cur->data.tenHP << " (Diem hien tai: " << cur->data.diem << ")\n";
        cur = cur->next;
    }

    string maHP;
    cout << "Nhap ma hoc phan can nhap/sua diem: ";
    getline(cin, maHP);

    cur = sv.headMonHoc;
    while (cur != nullptr) {
        if (cur->data.maHP == maHP) {
            double diemMoi;
            cout << "Nhap diem moi (0 - 10): ";
            cin >> diemMoi;
            cin.ignore(10000, '\n');
            if (diemMoi < 0.0 || diemMoi > 10.0) {
                cout << "Diem phai nam trong khoang 0 den 10!\n";
                return;
            }
            cur->data.diem = diemMoi;
            capNhatGPA(sv);
            cout << "Cap nhat diem thanh cong! GPA he 10 moi: " << sv.gpa10 << "\n";
            return;
        }
        cur = cur->next;
    }
    cout << "Khong tim thay hoc phan " << maHP << ".\n";
}

double quyDoiDiemHe4(double diem) {
    if (diem >= 8.5) return 4.0;
    if (diem >= 8.0) return 3.5;
    if (diem >= 7.0) return 3.0;
    if (diem >= 6.5) return 2.5;
    if (diem >= 5.5) return 2.0;
    if (diem >= 5.0) return 1.5;
    if (diem >= 4.0) return 1.0;
    return 0.0;
}

double tinhGPAHe10(const SinhVien& sv) {
    double tongDiem = 0.0;
    int tongTinChi = 0;

    NodeMonHoc* cur = sv.headMonHoc;
    while (cur != nullptr) {
        const MonHoc& hp = cur->data;
        if (hp.soTinChi > 0 && hp.diem >= 0.0 && hp.diem <= 10.0) {
            tongDiem += hp.diem * hp.soTinChi;
            tongTinChi += hp.soTinChi;
        }
        cur = cur->next;
    }
    return tongTinChi == 0 ? 0.0 : tongDiem / tongTinChi;
}

double tinhGPAHe4(const SinhVien& sv) {
    double tongDiem = 0.0;
    int tongTinChi = 0;

    NodeMonHoc* cur = sv.headMonHoc;
    while (cur != nullptr) {
        const MonHoc& hp = cur->data;
        if (hp.soTinChi > 0 && hp.diem >= 0.0 && hp.diem <= 10.0) {
            tongDiem += quyDoiDiemHe4(hp.diem) * hp.soTinChi;
            tongTinChi += hp.soTinChi;
        }
        cur = cur->next;
    }
    return tongTinChi == 0 ? 0.0 : tongDiem / tongTinChi;
}

string xepLoaiHocLuc(double gpa10) {
    if (gpa10 >= 8.5) return "Xuat sac";
    if (gpa10 >= 7.0) return "Gioi";
    if (gpa10 >= 5.5) return "Kha";
    if (gpa10 >= 4.0) return "Trung binh";
    return "Yeu";
}

void capNhatGPA(SinhVien& sv) {
    sv.gpa10 = tinhGPAHe10(sv);
    sv.gpa4 = tinhGPAHe4(sv);
}

void inBangDiem(const SinhVien& sv) {
    cout << "\n========== BANG DIEM SINH VIEN ==========\n";
    cout << "Ma SV: " << sv.maSV << "\nHo ten: " << sv.hoTen
         << "\nLop: " << sv.lop << "\nNgay sinh: " << sv.ngaySinh << "\n";
    cout << left << setw(14) << "Ma hoc phan"
         << setw(24) << "Ten hoc phan"
         << setw(10) << "Tin chi"
         << setw(12) << "Diem he 10" << "\n";
    cout << string(60, '-') << "\n";

    NodeMonHoc* cur = sv.headMonHoc;
    while (cur != nullptr) {
        const MonHoc& hp = cur->data;
        cout << left << setw(14) << hp.maHP
             << setw(24) << hp.tenHP
             << setw(10) << hp.soTinChi
             << fixed << setprecision(2) << hp.diem << "\n";
        cur = cur->next;
    }

    SinhVien tam;
    saoChepSinhVien(tam, sv);
    capNhatGPA(tam);
    cout << string(60, '-') << "\n";
    cout << fixed << setprecision(2)
         << "GPA he 10: " << tam.gpa10
         << "\nGPA he 4 : " << tam.gpa4
         << "\nXep loai : " << xepLoaiHocLuc(tam.gpa10) << "\n";
    cout << "========================================\n";
    giaiPhongSinhVien(tam);
}
