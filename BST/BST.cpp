#include "BST.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace {
    BSTNode* timMinNodeBST(BSTNode* node) {
        BSTNode* cur = node;
        while (cur != nullptr && cur->left != nullptr) {
            cur = cur->left;
        }
        return cur;
    }

    BSTNode* insertBSTRecursive(BSTNode* node, const SinhVien& sv, bool& thanhCong) {
        if (node == nullptr) {
            thanhCong = true;
            return taoBSTNode(sv);
        }

        if (sv.mssv < node->data.mssv) {
            node->left = insertBSTRecursive(node->left, sv, thanhCong);
        } else if (sv.mssv > node->data.mssv) {
            node->right = insertBSTRecursive(node->right, sv, thanhCong);
        } else {
            // Trung MSSV -> khong chen trung
            thanhCong = false;
        }

        return node;
    }

    void ganThongTinBST(SinhVien& dich, const SinhVien& nguon) {
        giaiPhongSinhVien(dich);
        dich.mssv = nguon.mssv;
        dich.hoTen = nguon.hoTen;
        dich.lop = nguon.lop;
        dich.ngaySinh = nguon.ngaySinh;
        dich.dsHocPhan = saoChepDSLK(nguon.dsHocPhan);
    }
}

BSTNode* taoBSTNode(const SinhVien& sv) {
    BSTNode* node = new BSTNode;
    node->data.mssv = sv.mssv;
    node->data.hoTen = sv.hoTen;
    node->data.lop = sv.lop;
    node->data.ngaySinh = sv.ngaySinh;
    node->data.dsHocPhan = saoChepDSLK(sv.dsHocPhan);
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

BSTNode* insertBST(BSTNode* root, const SinhVien& sv, bool& thanhCong) {
    thanhCong = false;
    if (!kiemTraSinhVienHopLe(sv)) {
        return root;
    }
    return insertBSTRecursive(root, sv, thanhCong);
}

BSTNode* removeBST(BSTNode* root, const string& mssv, bool& thanhCong) {
    if (root == nullptr) {
        thanhCong = false;
        return nullptr;
    }

    if (mssv < root->data.mssv) {
        root->left = removeBST(root->left, mssv, thanhCong);
    } else if (mssv > root->data.mssv) {
        root->right = removeBST(root->right, mssv, thanhCong);
    } else {
        thanhCong = true;

        // Truong hop 0 hoac 1 con
        if (root->left == nullptr) {
            BSTNode* temp = root->right;
            giaiPhongSinhVien(root->data);
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            BSTNode* temp = root->left;
            giaiPhongSinhVien(root->data);
            delete root;
            return temp;
        }

        // Truong hop 2 con: thay bang nut nho nhat cay con phai
        BSTNode* minRight = timMinNodeBST(root->right);
        ganThongTinBST(root->data, minRight->data);

        bool xoaNutTheMang = false;
        root->right = removeBST(root->right, minRight->data.mssv, xoaNutTheMang);
    }

    return root;
}

BSTNode* searchBST(BSTNode* root, const string& mssv) {
    BSTNode* cur = root;
    while (cur != nullptr) {
        if (mssv == cur->data.mssv) {
            return cur;
        }
        if (mssv < cur->data.mssv) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return nullptr;
}

int getHeightBST(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + max(getHeightBST(root->left), getHeightBST(root->right));
}

int demSoNutBST(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + demSoNutBST(root->left) + demSoNutBST(root->right);
}

void duyetLNR_BST(BSTNode* root) {
    if (root == nullptr) {
        return;
    }
    duyetLNR_BST(root->left);
    xuatSinhVien(root->data);
    duyetLNR_BST(root->right);
}

void giaiPhongBST(BSTNode*& root) {
    if (root == nullptr) {
        return;
    }
    giaiPhongBST(root->left);
    giaiPhongBST(root->right);
    giaiPhongSinhVien(root->data);
    delete root;
    root = nullptr;
}