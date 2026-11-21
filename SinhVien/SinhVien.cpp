#include "SinhVien.h"
#include <limits>

using namespace std;

SinhVien::SinhVien()
{
    MSSV = "";
    HoTen = "";
    Lop = "";
    NgaySinh = "";
    KhoiTaoDanhSach(dsHocPhan);
}

// Sao chep sau danh sach hoc phan de tranh hai sinh vien dung chung mot vung nho.
SinhVien::SinhVien(const SinhVien& sv)
{
    MSSV = sv.MSSV;
    HoTen = sv.HoTen;
    Lop = sv.Lop;
    NgaySinh = sv.NgaySinh;
    KhoiTaoDanhSach(dsHocPhan);
    SaoChepDanhSach(dsHocPhan, sv.dsHocPhan);
}

SinhVien& SinhVien::operator=(const SinhVien& sv)
{
    if (this != &sv)
    {
        MSSV = sv.MSSV;
        HoTen = sv.HoTen;
        Lop = sv.Lop;
        NgaySinh = sv.NgaySinh;
        SaoChepDanhSach(dsHocPhan, sv.dsHocPhan);
    }

    return *this;
}

SinhVien::~SinhVien()
{
    GiaiPhongDanhSach(dsHocPhan);
}

bool KiemTraNgaySinh(const string& ngaySinh)
{
    // Dinh dang yeu cau: DD/MM/YYYY
    if (ngaySinh.length() != 10)
        return false;

    if (ngaySinh[2] != '/' || ngaySinh[5] != '/')
        return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
            continue;

        if (ngaySinh[i] < '0' || ngaySinh[i] > '9')
            return false;
    }

    int ngay = (ngaySinh[0] - '0') * 10 + (ngaySinh[1] - '0');
    int thang = (ngaySinh[3] - '0') * 10 + (ngaySinh[4] - '0');
    int nam = (ngaySinh[6] - '0') * 1000
            + (ngaySinh[7] - '0') * 100
            + (ngaySinh[8] - '0') * 10
            + (ngaySinh[9] - '0');

    if (nam <= 0 || thang < 1 || thang > 12)
        return false;

    int soNgayTrongThang[] = { 31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31 };

    bool namNhuan = (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);

    if (namNhuan)
        soNgayTrongThang[1] = 29;

    if (ngay < 1 || ngay > soNgayTrongThang[thang - 1])
        return false;

    return true;
}

bool KiemTraSinhVienHopLe(const SinhVien& sv)
{
    if (sv.MSSV.empty() || sv.HoTen.empty() || sv.Lop.empty())
        return false;

    if (!KiemTraNgaySinh(sv.NgaySinh))
        return false;

    return true;
}

void NhapSinhVien(SinhVien& sv)
{
    cout << "Nhap MSSV: ";
    getline(cin >> ws, sv.MSSV);

    cout << "Nhap ho ten: ";
    getline(cin, sv.HoTen);

    cout << "Nhap lop: ";
    getline(cin, sv.Lop);

    while (true)
    {
        cout << "Nhap ngay sinh (DD/MM/YYYY): ";
        getline(cin, sv.NgaySinh);

        if (KiemTraNgaySinh(sv.NgaySinh))
            break;

        cout << "Ngay sinh khong hop le. Vi du: 15/03/2005\n";
    }
}

void XuatSinhVien(const SinhVien& sv)
{
    cout << "MSSV     : " << sv.MSSV << '\n';
    cout << "Ho ten   : " << sv.HoTen << '\n';
    cout << "Lop      : " << sv.Lop << '\n';
    cout << "Ngay sinh: " << sv.NgaySinh << '\n';
}
