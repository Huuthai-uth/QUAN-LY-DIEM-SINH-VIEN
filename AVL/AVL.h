#pragma once
#include "../SinhVien/SinhVien.h"
#include <string>

struct AVLNode {
    SinhVien data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

// Các hàm tính chiều cao và hệ số cân bằng (Balance Factor = height(left) - height(right))
int getHeight(AVLNode* node);
int getBalance(AVLNode* node);
void updateHeight(AVLNode* node);

// Các phép xoay cân bằng cây (LL, RR, LR, RL)
AVLNode* rotateRight(AVLNode* y);
AVLNode* rotateLeft(AVLNode* x);
AVLNode* balanceNode(AVLNode* node);

// Thao tác chính trên cây AVL (khóa MSSV)
AVLNode* taoAVLNode(const SinhVien& sv);
AVLNode* insertAVL(AVLNode* root, const SinhVien& sv, bool& thanhCong);
AVLNode* removeAVL(AVLNode* root, const std::string& mssv, bool& thanhCong);
AVLNode* searchAVL(AVLNode* root, const std::string& mssv);

// Duyệt cây LNR in danh sách theo MSSV & hiển thị cây kèm hệ số cân bằng
void duyetLNR_AVL(AVLNode* root);
void inCayAVL_KemCanBang(AVLNode* root, int space = 0, int indent = 6);

// Giải phóng toàn bộ cây AVL (kèm giải phóng DSLK học phần của từng sinh viên)
void giaiPhongAVL(AVLNode*& root);