#pragma once
#include "../SinhVien/SinhVien.h"
#include <string>

struct BSTNode {
    SinhVien data;
    BSTNode* left;
    BSTNode* right;
};

// Thao tác cơ bản trên cây BST thường (dùng để so sánh thực nghiệm với AVL)
BSTNode* taoBSTNode(const SinhVien& sv);
BSTNode* insertBST(BSTNode* root, const SinhVien& sv, bool& thanhCong);
BSTNode* removeBST(BSTNode* root, const std::string& mssv, bool& thanhCong);
BSTNode* searchBST(BSTNode* root, const std::string& mssv);

// Tính chiều cao và duyệt cây
int getHeightBST(BSTNode* root);
void duyetLNR_BST(BSTNode* root);

// Giải phóng toàn bộ cây BST
void giaiPhongBST(BSTNode*& root);