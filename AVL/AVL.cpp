#include "AVL.h"
#include <iostream>
#include <algorithm>

using namespace std;

int getHeight(AVLNode* node) {
    return (node == nullptr) ? 0 : node->height;
}

int getBalance(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(AVLNode* node) {
    if (node != nullptr) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

AVLNode* rotateRight(AVLNode* y) {
    if (y == nullptr || y->left == nullptr) {
        return y;
    }
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    if (x == nullptr || x->right == nullptr) {
        return x;
    }
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLNode* balanceNode(AVLNode* node) {
    if (node == nullptr) {
        return nullptr;
    }

    updateHeight(node);
    int balance = getBalance(node);

    // Lệch trái - trái (LL)
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    // Lệch trái - phải (LR)
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Lệch phải - phải (RR)
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Lệch phải - trái (RL)
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLNode* taoAVLNode(const SinhVien& sv) {
    AVLNode* node = new AVLNode;
    node->data = sv;
    node->data.dsHocPhan = saoChepDSLK(sv.dsHocPhan);
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

AVLNode* insertAVL(AVLNode* root, const SinhVien& sv, bool& thanhCong) {
    if (!kiemTraSinhVienHopLe(sv)) {
        thanhCong = false;
        return root;
    }

    if (root == nullptr) {
        thanhCong = true;
        return taoAVLNode(sv);
    }

    if (sv.mssv < root->data.mssv) {
        root->left = insertAVL(root->left, sv, thanhCong);
    } else if (sv.mssv > root->data.mssv) {
        root->right = insertAVL(root->right, sv, thanhCong);
    } else {
        // Trùng MSSV -> không chèn trùng
        thanhCong = false;
        return root;
    }

    if (!thanhCong) {
        return root;
    }

    return balanceNode(root);
}

namespace {
    AVLNode* timMinNodeAVL(AVLNode* node) {
        AVLNode* cur = node;
        while (cur != nullptr && cur->left != nullptr) {
            cur = cur->left;
        }
        return cur;
    }
}

AVLNode* removeAVL(AVLNode* root, const string& mssv, bool& thanhCong) {
    if (root == nullptr) {
        thanhCong = false;
        return nullptr;
    }

    if (mssv < root->data.mssv) {
        root->left = removeAVL(root->left, mssv, thanhCong);
    } else if (mssv > root->data.mssv) {
        root->right = removeAVL(root->right, mssv, thanhCong);
    } else {
        thanhCong = true;

        // Trường hợp 0 hoặc 1 con
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = (root->left != nullptr) ? root->left : root->right;
            giaiPhongSinhVien(root->data);
            delete root;
            return temp;
        }

        // Trường hợp 2 con: lấy nút nhỏ nhất cây con phải làm nút thế mạng
        AVLNode* temp = timMinNodeAVL(root->right);
        giaiPhongSinhVien(root->data);
        root->data.mssv = temp->data.mssv;
        root->data.hoTen = temp->data.hoTen;
        root->data.lop = temp->data.lop;
        root->data.ngaySinh = temp->data.ngaySinh;
        root->data.dsHocPhan = saoChepDSLK(temp->data.dsHocPhan);

        bool dummy = false;
        root->right = removeAVL(root->right, temp->data.mssv, dummy);
    }

    return balanceNode(root);
}

AVLNode* searchAVL(AVLNode* root, const string& mssv) {
    AVLNode* cur = root;
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

void duyetLNR_AVL(AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    duyetLNR_AVL(root->left);
    xuatSinhVien(root->data);
    duyetLNR_AVL(root->right);
}

void inCayAVL_KemCanBang(AVLNode* root, int space, int indent) {
    if (root == nullptr) {
        return;
    }

    space += indent;

    inCayAVL_KemCanBang(root->right, space, indent);

    cout << '\n';
    for (int i = indent; i < space; ++i) {
        cout << ' ';
    }
    cout << root->data.mssv << " (h=" << root->height
         << ", bf=" << getBalance(root) << ")\n";

    inCayAVL_KemCanBang(root->left, space, indent);
}

void giaiPhongAVL(AVLNode*& root) {
    if (root == nullptr) {
        return;
    }
    giaiPhongAVL(root->left);
    giaiPhongAVL(root->right);
    giaiPhongSinhVien(root->data);
    delete root;
    root = nullptr;
}