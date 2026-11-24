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