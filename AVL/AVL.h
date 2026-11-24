#pragma once
#include "../SinhVien/SinhVien.h"
#include <string>

struct AVLNode {
    SinhVien data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

// Tinh chieu cao va he so can bang (BF = height(left) - height(right))
int getHeight(AVLNode* node);
int getBalance(AVLNode* node);
void updateHeight(AVLNode* node);

// Cac phep xoay can bang (LL, RR, LR, RL)
AVLNode* rotateRight(AVLNode* y);
AVLNode* rotateLeft(AVLNode* x);
AVLNode* balanceNode(AVLNode* node);

// Thao tac chinh tren cay AVL (khoa MSSV)
AVLNode* taoAVLNode(const SinhVien& sv);
AVLNode* insertAVL(AVLNode* root, const SinhVien& sv, bool& thanhCong);
AVLNode* removeAVL(AVLNode* root, const std::string& mssv, bool& thanhCong);
AVLNode* searchAVL(AVLNode* root, const std::string& mssv);

// Duyet cay LNR, hien thi cay kem he so can bang va dem so nut
void duyetLNR_AVL(AVLNode* root);
void inCayAVL_KemCanBang(AVLNode* root, int space = 0, int indent = 6);
int demSoNutAVL(AVLNode* root);

// Giai phong toan bo cay AVL va danh sach hoc phan ben trong
void giaiPhongAVL(AVLNode*& root);