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

// Tinh chieu cao, dem so nut va duyet cay (khu de quy an toan cho du lieu lon)
int getHeightBST(BSTNode* root);
int demSoNutBST(BSTNode* root);
void duyetLNR_BST(BSTNode* root);

// Kiem thu tinh hop le va truong hop cay bi lech
bool kiemTraBSTHopLe(BSTNode* root);
bool laCayLechHoanToanBST(BSTNode* root);
void inThongTinKiemThuBST(BSTNode* root);

// Giai phong toan bo cay BST
void giaiPhongBST(BSTNode*& root);