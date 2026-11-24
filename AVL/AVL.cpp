#include "AVL.h"
#include <iostream>

using namespace std;

namespace {
    int maxInt(int a, int b) {
        return (a > b) ? a : b;
    }

    AVLNode* timMinNodeAVL(AVLNode* node) {
        AVLNode* cur = node;
        while (cur != nullptr && cur->left != nullptr) {
            cur = cur->left;
        }
        return cur;
    }

    AVLNode* insertAVLRecursive(AVLNode* node, const SinhVien& sv, bool& thanhCong) {
        if (node == nullptr) {
            thanhCong = true;
            return taoAVLNode(sv);
        }

        if (sv.mssv < node->data.mssv) {
            node->left = insertAVLRecursive(node->left, sv, thanhCong);
        } else if (sv.mssv > node->data.mssv) {
            node->right = insertAVLRecursive(node->right, sv, thanhCong);
        } else {
            // Trung MSSV -> khong chen trung
            thanhCong = false;
            return node;
        }

        if (!thanhCong) {
            return node;
        }

        return balanceNode(node);
    }

    void ganThongTinSinhVien(SinhVien& dich, const SinhVien& nguon) {
        giaiPhongSinhVien(dich);
        dich.mssv = nguon.mssv;
        dich.hoTen = nguon.hoTen;
        dich.lop = nguon.lop;
        dich.ngaySinh = nguon.ngaySinh;
        dich.dsHocPhan = saoChepDSLK(nguon.dsHocPhan);
    }
}

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
        node->height = 1 + maxInt(getHeight(node->left), getHeight(node->right));
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

    // Lech trai - trai (LL)
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    // Lech trai - phai (LR)
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Lech phai - phai (RR)
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Lech phai - trai (RL)
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLNode* taoAVLNode(const SinhVien& sv) {
    AVLNode* node = new AVLNode;
    node->data.mssv = sv.mssv;
    node->data.hoTen = sv.hoTen;
    node->data.lop = sv.lop;
    node->data.ngaySinh = sv.ngaySinh;
    node->data.dsHocPhan = saoChepDSLK(sv.dsHocPhan);
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

AVLNode* insertAVL(AVLNode* root, const SinhVien& sv, bool& thanhCong) {
    thanhCong = false;
    if (!kiemTraSinhVienHopLe(sv)) {
        return root;
    }
    return insertAVLRecursive(root, sv, thanhCong);
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

        // Truong hop 0 hoac 1 con
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = (root->left != nullptr) ? root->left : root->right;
            giaiPhongSinhVien(root->data);
            delete root;
            return temp;
        }

        // Truong hop 2 con: thay bang nut nho nhat cay con phai
        AVLNode* minRight = timMinNodeAVL(root->right);
        ganThongTinSinhVien(root->data, minRight->data);

        bool xoaNutTheMang = false;
        root->right = removeAVL(root->right, minRight->data.mssv, xoaNutTheMang);
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

int demSoNutAVL(AVLNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + demSoNutAVL(root->left) + demSoNutAVL(root->right);
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