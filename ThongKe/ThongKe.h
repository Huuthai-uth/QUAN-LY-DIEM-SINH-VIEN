#pragma once
#include <string>
#include "../AVL/AVL.h"
#include "../QuanLyDiem/QuanLyDiem.h"

// Thong ke so luong sinh vien theo tung lop (duyet cay AVL)
void thongKeTheoLopAVL(AVLNode* root);

// Thong ke so luong sinh vien theo xep loai hoc luc (Xuat sac, Gioi, Kha, Trung binh, Yeu, Chua co diem)
void thongKeHocLucAVL(AVLNode* root);

// Liet ke va thong ke sinh vien bi canh bao hoc vu (GPA he 4 < 1.0)
void canhBaoHocVuAVL(AVLNode* root);

// In danh sach TOP 10 sinh vien co GPA cao nhat toan truong (dung Quick Sort giam dan)
void top10SinhVienAVL(AVLNode* root, bool uuTienHe4 = false);