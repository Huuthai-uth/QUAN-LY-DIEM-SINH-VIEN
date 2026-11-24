#include "LinkedList.h"
#include <iostream>
#include <iomanip>

using namespace std;

void themHocPhan(HocPhan*& head, HocPhan* hpMoi) {
    if (hpMoi == nullptr) {
        return;
    }
    hpMoi->next = nullptr;

    if (head == nullptr) {
        head = hpMoi;
        return;
    }

    // Neu trung ma hoc phan thi cap nhat ten, tin chi va diem, giai phong hpMoi
    HocPhan* cur = head;
    while (cur != nullptr) {
        if (cur->maHP == hpMoi->maHP) {
            cur->tenHP = hpMoi->tenHP;
            cur->soTinChi = hpMoi->soTinChi;
            cur->diemHe10 = hpMoi->diemHe10;
            delete hpMoi;
            return;
        }
        if (cur->next == nullptr) {
            break;
        }
        cur = cur->next;
    }

    cur->next = hpMoi;
}

bool xoaHocPhan(HocPhan*& head, const string& maHP) {
    if (head == nullptr) {
        return false;
    }

    if (head->maHP == maHP) {
        HocPhan* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    HocPhan* prev = head;
    HocPhan* cur = head->next;
    while (cur != nullptr) {
        if (cur->maHP == maHP) {
            prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }

    return false;
}

HocPhan* timHocPhan(HocPhan* head, const string& maHP) {
    HocPhan* cur = head;
    while (cur != nullptr) {
        if (cur->maHP == maHP) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

bool suaDiemHocPhan(HocPhan* head, const string& maHP, float diemMoi) {
    if (!kiemTraDiem(diemMoi)) {
        return false;
    }
    HocPhan* hp = timHocPhan(head, maHP);
    if (hp == nullptr) {
        return false;
    }
    hp->diemHe10 = diemMoi;
    return true;
}

void xuatDanhSachHocPhan(const HocPhan* head) {
    if (head == nullptr) {
        cout << "  (Chua co du lieu hoc phan)\n";
        return;
    }
    cout << left << setw(12) << "Ma HP"
         << setw(28) << "Ten HP"
         << setw(10) << "Tin chi"
         << setw(10) << "Diem 10" << '\n';
    const HocPhan* cur = head;
    while (cur != nullptr) {
        xuatHocPhan(cur);
        cur = cur->next;
    }
}

int demSoHocPhan(const HocPhan* head) {
    int count = 0;
    const HocPhan* cur = head;
    while (cur != nullptr) {
        ++count;
        cur = cur->next;
    }
    return count;
}

void giaiPhongDSLK(HocPhan*& head) {
    while (head != nullptr) {
        HocPhan* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

HocPhan* saoChepDSLK(const HocPhan* head) {
    if (head == nullptr) {
        return nullptr;
    }
    HocPhan* newHead = nullptr;
    HocPhan* newTail = nullptr;
    const HocPhan* cur = head;

    while (cur != nullptr) {
        HocPhan* nodeMoi = taoHocPhan(cur->maHP, cur->tenHP, cur->soTinChi, cur->diemHe10);
        if (nodeMoi != nullptr) {
            if (newHead == nullptr) {
                newHead = nodeMoi;
                newTail = nodeMoi;
            } else {
                newTail->next = nodeMoi;
                newTail = nodeMoi;
            }
        }
        cur = cur->next;
    }
    return newHead;
}