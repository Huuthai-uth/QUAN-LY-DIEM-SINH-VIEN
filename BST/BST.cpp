#include "BST.h"
#include <iostream>

using namespace std;

namespace {
    // Giup khu de quy de tranh Stack Overflow khi cay lech >= 10.000 nut
    struct BSTStackItem {
        BSTNode* node;
        int depth;
        BSTStackItem* next;
    };

    void pushStack(BSTStackItem*& top, BSTNode* node, int depth = 0) {
        BSTStackItem* item = new BSTStackItem;
        item->node = node;
        item->depth = depth;
        item->next = top;
        top = item;
    }

    BSTStackItem popStack(BSTStackItem*& top) {
        BSTStackItem* temp = top;
        BSTStackItem val = *temp;
        top = top->next;
        delete temp;
        return val;
    }

    void clearStack(BSTStackItem*& top) {
        while (top != nullptr) {
            BSTStackItem* temp = top;
            top = top->next;
            delete temp;
        }
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

    if (root == nullptr) {
        thanhCong = true;
        return taoBSTNode(sv);
    }

    BSTNode* cur = root;
    BSTNode* parent = nullptr;

    while (cur != nullptr) {
        parent = cur;
        if (sv.mssv < cur->data.mssv) {
            cur = cur->left;
        } else if (sv.mssv > cur->data.mssv) {
            cur = cur->right;
        } else {
            // Trung MSSV -> khong chen trung
            return root;
        }
    }

    BSTNode* newNode = taoBSTNode(sv);
    if (sv.mssv < parent->data.mssv) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    thanhCong = true;
    return root;
}

BSTNode* removeBST(BSTNode* root, const string& mssv, bool& thanhCong) {
    thanhCong = false;
    BSTNode* cur = root;
    BSTNode* parent = nullptr;

    // Tim nut can xoa va nut cha cua no
    while (cur != nullptr && cur->data.mssv != mssv) {
        parent = cur;
        if (mssv < cur->data.mssv) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if (cur == nullptr) {
        return root;
    }

    thanhCong = true;

    // Truong hop 2 con: tim nut nho nhat ben cay con phai de the mang
    if (cur->left != nullptr && cur->right != nullptr) {
        BSTNode* minParent = cur;
        BSTNode* minRight = cur->right;
        while (minRight->left != nullptr) {
            minParent = minRight;
            minRight = minRight->left;
        }

        ganThongTinBST(cur->data, minRight->data);

        // Chuyen sang xoa nut the mang (toi da 1 con phai)
        cur = minRight;
        parent = minParent;
    }

    // Truong hop 0 hoac 1 con
    BSTNode* child = (cur->left != nullptr) ? cur->left : cur->right;

    if (parent == nullptr) {
        root = child;
    } else if (parent->left == cur) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    giaiPhongSinhVien(cur->data);
    delete cur;
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

    BSTStackItem* top = nullptr;
    pushStack(top, root, 1);
    int maxHeight = 0;

    while (top != nullptr) {
        BSTStackItem item = popStack(top);
        if (item.depth > maxHeight) {
            maxHeight = item.depth;
        }
        if (item.node->left != nullptr) {
            pushStack(top, item.node->left, item.depth + 1);
        }
        if (item.node->right != nullptr) {
            pushStack(top, item.node->right, item.depth + 1);
        }
    }

    return maxHeight;
}

int demSoNutBST(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }

    BSTStackItem* top = nullptr;
    pushStack(top, root);
    int count = 0;

    while (top != nullptr) {
        BSTNode* cur = popStack(top).node;
        ++count;
        if (cur->left != nullptr) {
            pushStack(top, cur->left);
        }
        if (cur->right != nullptr) {
            pushStack(top, cur->right);
        }
    }

    return count;
}

void duyetLNR_BST(BSTNode* root) {
    BSTStackItem* top = nullptr;
    BSTNode* cur = root;

    while (cur != nullptr || top != nullptr) {
        while (cur != nullptr) {
            pushStack(top, cur);
            cur = cur->left;
        }
        cur = popStack(top).node;
        xuatSinhVien(cur->data);
        cur = cur->right;
    }
}

bool kiemTraBSTHopLe(BSTNode* root) {
    BSTStackItem* top = nullptr;
    BSTNode* cur = root;
    const string* prevKey = nullptr;

    while (cur != nullptr || top != nullptr) {
        while (cur != nullptr) {
            pushStack(top, cur);
            cur = cur->left;
        }
        cur = popStack(top).node;

        if (prevKey != nullptr && cur->data.mssv <= *prevKey) {
            clearStack(top);
            return false;
        }
        prevKey = &cur->data.mssv;
        cur = cur->right;
    }

    return true;
}

bool laCayLechHoanToanBST(BSTNode* root) {
    // Cay rong hoac chi co 1 nut khong tinh la bi lech
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return false;
    }

    BSTNode* cur = root;
    while (cur != nullptr) {
        if (cur->left != nullptr && cur->right != nullptr) {
            return false;
        }
        cur = (cur->left != nullptr) ? cur->left : cur->right;
    }
    return true;
}

void inThongTinKiemThuBST(BSTNode* root) {
    int soNut = demSoNutBST(root);
    int chieuCao = getHeightBST(root);
    bool hopLe = kiemTraBSTHopLe(root);
    bool lechHoanToan = laCayLechHoanToanBST(root);

    cout << "So nut BST            : " << soNut << '\n';
    cout << "Chieu cao BST         : " << chieuCao << '\n';
    cout << "Tinh chat BST hop le  : " << (hopLe ? "CO" : "KHONG") << '\n';
    cout << "Trang thai cay lech   : "
         << (lechHoanToan ? "BI LECH HOAN TOAN (h == n)" : "Khong lech hoan toan") << '\n';
}

void giaiPhongBST(BSTNode*& root) {
    if (root == nullptr) {
        return;
    }

    BSTStackItem* top = nullptr;
    pushStack(top, root);

    while (top != nullptr) {
        BSTNode* cur = popStack(top).node;
        if (cur->left != nullptr) {
            pushStack(top, cur->left);
        }
        if (cur->right != nullptr) {
            pushStack(top, cur->right);
        }
        giaiPhongSinhVien(cur->data);
        delete cur;
    }

    root = nullptr;
}