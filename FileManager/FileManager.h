#pragma once
#include "../AVL/AVL.h"
#include "../BST/BST.h"
#include <string>

#ifndef KET_QUA_FILE_DEFINED
#define KET_QUA_FILE_DEFINED
struct KetQuaFile {
    bool thanhCong = false;
    int soDongHopLe = 0;
    int soDongLoi = 0;
    std::string thongBao;
};
#endif

// Doc du lieu sinh vien tu file (MSSV|HoTen|Lop|NgaySinh) va nap vao cay AVL
KetQuaFile docVaNapSinhVienAVL(const std::string& duongDanFile, AVLNode*& rootAVL);

// Doc du lieu hoc phan tu file (MSSV|MaHP|TenHP|SoTinChi|DiemHe10) va gan vao cay AVL
KetQuaFile docVaGanHocPhanAVL(const std::string& duongDanFile, AVLNode* rootAVL);

// Nap tong hop ca 2 file sinh vien va hoc phan vao cay AVL
KetQuaFile napDuLieuTongHopAVL(const std::string& fileSinhVien,
                                const std::string& fileHocPhan,
                                AVLNode*& rootAVL);

// Nap tong hop ca 2 file sinh vien va hoc phan vao cay BST (phuc vu so sanh thuc nghiem)
KetQuaFile napDuLieuTongHopBST(const std::string& fileSinhVien,
                                const std::string& fileHocPhan,
                                BSTNode*& rootBST);

// Ghi du lieu sinh vien va danh sach hoc phan tu cay AVL ra file
KetQuaFile ghiDuLieuRaFileAVL(AVLNode* rootAVL,
                              const std::string& fileSinhVien,
                              const std::string& fileHocPhan);

const int SO_LUONG_DU_LIEU_LON_MAC_DINH = 10000;
const int SO_LAN_TIM_KIEM_THUC_NGHIEM = 1000;

// Sinh bo du lieu lon ngau nhien (>= 10^4 ban ghi, khong trung MSSV) va tuy chon ghi ra file
void taoBoDuLieuLonNgauNhien(int soLuong,
                              SinhVien*& dsSinhVien,
                              int& soLuongThucTe,
                              const std::string& duongDanFileGhi = "");

// Do thoi gian chen va tim kiem tren cay AVL va BST (ho tro ca du lieu ngau nhien va tang dan)
void thucNghiemAVLvaBST(int soLuong = SO_LUONG_DU_LIEU_LON_MAC_DINH,
                         bool duLieuTangDan = false,
                         const std::string& duongDanFileGhi = "");