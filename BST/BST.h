#pragma once
#include "../SinhVien/SinhVien.h"
#include <string>

struct BSTNode {
    SinhVien data;
    BSTNode* left;
    BSTNode* right;
};

// Thao tac co ban tren cay BST thuong (dung de so sanh thuc nghiem voi AVL)
BSTNode* taoBSTNode(const SinhVien& sv);
BSTNode* insertBST(BSTNode* root, const SinhVien& sv, bool& thanhCong);
BSTNode* removeBST(BSTNode* root, const std::string& mssv, bool& thanhCong);
BSTNode* searchBST(BSTNode* root, const std::string& mssv);

// Tinh chieu cao, dem so nut va duyet cay
int getHeightBST(BSTNode* root);
int demSoNutBST(BSTNode* root);
void duyetLNR_BST(BSTNode* root);

// Giai phong toan bo cay BST
void giaiPhongBST(BSTNode*& root);