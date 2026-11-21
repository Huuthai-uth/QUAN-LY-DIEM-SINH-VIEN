#include <iostream>
#include "SinhVien.h"
#include "HocPhan.h"
#include "LinkedList.h"

using namespace std;

int main()
{
    SinhVien sv;

    cout << "========== NHAP SINH VIEN ==========\n";
    NhapSinhVien(sv);

    int n;

    cout << "\nNhap so hoc phan: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "\n========== HOC PHAN " << i + 1 << " ==========\n";

        HocPhan hp;
        NhapHocPhan(hp);

        if (ThemHocPhan(sv.dsHocPhan, hp))
        {
            cout << "Them hoc phan thanh cong!\n";
        }
        else
        {
            cout << "Them hoc phan that bai!\n";
        }
    }

    cout << "\n========== THONG TIN SINH VIEN ==========\n";
    XuatSinhVien(sv);

    cout << "\n========== DANH SACH HOC PHAN ==========\n";
    InDanhSachHocPhan(sv.dsHocPhan);

    cout << "\nTong so hoc phan: "
         << DemHocPhan(sv.dsHocPhan) << endl;

    cout << "\n========== KIEM TRA TIM KIEM ==========\n";

    string maHP;
    cout << "Nhap ma hoc phan can tim: ";
    cin >> maHP;

    NodeHocPhan* p = TimHocPhan(sv.dsHocPhan, maHP);

    if (p != NULL)
    {
        cout << "Tim thay hoc phan!\n";
        XuatHocPhan(p->data);
    }
    else
    {
        cout << "Khong tim thay hoc phan!\n";
    }

    cout << "\n========== KET THUC ==========\n";

    return 0;
}
