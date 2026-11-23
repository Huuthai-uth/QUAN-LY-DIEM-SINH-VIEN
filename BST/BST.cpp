#include "BST.h"
#include <iostream>
#include <algorithm>

using namespace std;

BSTNode* taoBSTNode(const SinhVien& sv) {
    BSTNode* node = new BSTNode;
    node->data = sv;
    node->data.dsHocPhan = saoChepDSLK(sv.dsHocPhan);
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

BSTNode* insertBST(BSTNode* root, const SinhVien& sv, bool& thanhCong) {
    if (!kiemTraSinhVienHopLe(sv)) {
        thanhCong = false;
        return root;
    }

    if (root == nullptr) {
        thanhCong = true;
        return taoBSTNode(sv);
    }

    if (sv.mssv < root->data.mssv) {
        root->left = insertBST(root->left, sv, thanhCong);
    } else if (sv.mssv > root->data.mssv) {
        root->right = insertBST(root->right, sv, thanhCong);
    } else {
        thanhCong = false;
    }

    return root;
}

namespace {
    BSTNode* timMinNodeBST(BSTNode* node) {
        BSTNode* cur = node;
        while (cur != nullptr && cur->left != nullptr) {
            cur = cur->left;
        }
        return cur;
    }
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

        BSTNode* temp = timMinNodeBST(root->right);
        giaiPhongSinhVien(root->data);
        root->data.mssv = temp->data.mssv;
        root->data.hoTen = temp->data.hoTen;
        root->data.lop = temp->data.lop;
        root->data.ngaySinh = temp->data.ngaySinh;
        root->data.dsHocPhan = saoChepDSLK(temp->data.dsHocPhan);

        bool dummy = false;
        root->right = removeBST(root->right, temp->data.mssv, dummy);
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