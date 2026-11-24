#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>

using namespace std;

namespace {
    string loaiBoKyTuXuongDong(const string& s) {
        string res = s;
        while (!res.empty() && (res.back() == '\r' || res.back() == '\n')) {
            res.pop_back();
        }
        return res;
    }

    string catKhoangTrangHaiDau(const string& s) {
        size_t start = 0;
        while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
            ++start;
        }
        size_t end = s.size();
        while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
            --end;
        }
        return s.substr(start, end - start);
    }

    // Tach chuoi theo dau '|' vao mang dong string* (khong dung std::vector)
    string* tachTheoDauGachDung(const string& line, int& soPhanTu) {
        soPhanTu = 0;
        if (line.empty()) {
            return nullptr;
        }

        int dem = 1;
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '|') {
                ++dem;
            }
        }

        string* parts = new string[dem];
        int idx = 0;
        size_t start = 0;
        for (size_t i = 0; i <= line.size(); ++i) {
            if (i == line.size() || line[i] == '|') {
                string item = line.substr(start, i - start);
                parts[idx++] = loaiBoKyTuXuongDong(item);
                start = i + 1;
            }
        }

        soPhanTu = idx;
        return parts;
    }

    void giaiPhongMangString(string*& arr) {
        delete[] arr;
        arr = nullptr;
    }

    bool parseSoNguyenAnToan(const string& text, int& giaTri) {
        string clean = catKhoangTrangHaiDau(text);
        if (clean.empty()) {
            return false;
        }
        size_t i = 0;
        if (clean[0] == '+' || clean[0] == '-') {
            i = 1;
        }
        if (i >= clean.size()) {
            return false;
        }
        for (; i < clean.size(); ++i) {
            if (!isdigit(static_cast<unsigned char>(clean[i]))) {
                return false;
            }
        }
        try {
            size_t idx = 0;
            long long val = stoll(clean, &idx, 10);
            if (idx != clean.size() || val < -2147483648LL || val > 2147483647LL) {
                return false;
            }
            giaTri = static_cast<int>(val);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool parseSoThucFloatAnToan(const string& text, float& giaTri) {
        string clean = catKhoangTrangHaiDau(text);
        if (clean.empty()) {
            return false;
        }
        try {
            size_t idx = 0;
            float val = stof(clean, &idx);
            if (idx != clean.size() || !kiemTraDiem(val)) {
                return false;
            }
            giaTri = val;
            return true;
        } catch (...) {
            return false;
        }
    }

    void ghiDeQuyAVL(AVLNode* node, ofstream& outSV, ofstream& outHP,
                     int& tongSV, int& tongHP) {
        if (node == nullptr) {
            return;
        }

        ghiDeQuyAVL(node->left, outSV, outHP, tongSV, tongHP);

        const SinhVien& sv = node->data;
        outSV << sv.mssv << '|'
              << sv.hoTen << '|'
              << sv.lop << '|'
              << sv.ngaySinh << '\n';
        ++tongSV;

        const HocPhan* cur = sv.dsHocPhan;
        while (cur != nullptr) {
            outHP << sv.mssv << '|'
                  << cur->maHP << '|'
                  << cur->tenHP << '|'
                  << cur->soTinChi << '|'
                  << fixed << setprecision(2) << cur->diemHe10 << '\n';
            ++tongHP;
            cur = cur->next;
        }

        ghiDeQuyAVL(node->right, outSV, outHP, tongSV, tongHP);
    }
}

KetQuaFile docVaNapSinhVienAVL(const string& duongDanFile, AVLNode*& rootAVL) {
    KetQuaFile kq;
    ifstream ifs(duongDanFile);
    if (!ifs.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the mo file sinh vien: " + duongDanFile;
        return kq;
    }

    string line;
    while (getline(ifs, line)) {
        string cleanLine = loaiBoKyTuXuongDong(line);
        if (catKhoangTrangHaiDau(cleanLine).empty()) {
            continue;
        }

        int soPhanTu = 0;
        string* parts = tachTheoDauGachDung(cleanLine, soPhanTu);
        if (parts == nullptr || soPhanTu != 4) {
            giaiPhongMangString(parts);
            ++kq.soDongLoi;
            continue;
        }

        SinhVien sv = taoSinhVien(
            catKhoangTrangHaiDau(parts[0]),
            catKhoangTrangHaiDau(parts[1]),
            catKhoangTrangHaiDau(parts[2]),
            catKhoangTrangHaiDau(parts[3])
        );
        giaiPhongMangString(parts);

        bool chenThanhCong = false;
        rootAVL = insertAVL(rootAVL, sv, chenThanhCong);
        giaiPhongSinhVien(sv);

        if (chenThanhCong) {
            ++kq.soDongHopLe;
        } else {
            ++kq.soDongLoi;
        }
    }

    ifs.close();
    kq.thanhCong = true;
    kq.thongBao = "Doc sinh vien xong (" + to_string(kq.soDongHopLe) +
                  " hop le, " + to_string(kq.soDongLoi) + " dong loi/trung).";
    return kq;
}

KetQuaFile docVaGanHocPhanAVL(const string& duongDanFile, AVLNode* rootAVL) {
    KetQuaFile kq;
    if (rootAVL == nullptr) {
        kq.thanhCong = false;
        kq.thongBao = "Cay AVL rong, can nap danh sach sinh vien truoc khi doc hoc phan.";
        return kq;
    }

    ifstream ifs(duongDanFile);
    if (!ifs.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the mo file hoc phan: " + duongDanFile;
        return kq;
    }

    string line;
    while (getline(ifs, line)) {
        string cleanLine = loaiBoKyTuXuongDong(line);
        if (catKhoangTrangHaiDau(cleanLine).empty()) {
            continue;
        }

        int soPhanTu = 0;
        string* parts = tachTheoDauGachDung(cleanLine, soPhanTu);
        if (parts == nullptr || soPhanTu != 5) {
            giaiPhongMangString(parts);
            ++kq.soDongLoi;
            continue;
        }

        string mssv = catKhoangTrangHaiDau(parts[0]);
        string maHP = catKhoangTrangHaiDau(parts[1]);
        string tenHP = catKhoangTrangHaiDau(parts[2]);
        int soTinChi = 0;
        float diemHe10 = 0.0f;

        bool hopLeSo = parseSoNguyenAnToan(parts[3], soTinChi) &&
                       parseSoThucFloatAnToan(parts[4], diemHe10);
        giaiPhongMangString(parts);

        if (!hopLeSo) {
            ++kq.soDongLoi;
            continue;
        }

        HocPhan* hpMoi = taoHocPhan(maHP, tenHP, soTinChi, diemHe10);
        if (hpMoi == nullptr) {
            ++kq.soDongLoi;
            continue;
        }

        AVLNode* svNode = searchAVL(rootAVL, mssv);
        if (svNode == nullptr) {
            delete hpMoi;
            ++kq.soDongLoi;
            continue;
        }

        themHocPhan(svNode->data.dsHocPhan, hpMoi);
        ++kq.soDongHopLe;
    }

    ifs.close();
    kq.thanhCong = true;
    kq.thongBao = "Doc hoc phan xong (" + to_string(kq.soDongHopLe) +
                  " hop le, " + to_string(kq.soDongLoi) + " dong loi/khong tim thay SV).";
    return kq;
}

KetQuaFile napDuLieuTongHopAVL(const string& fileSinhVien,
                                const string& fileHocPhan,
                                AVLNode*& rootAVL) {
    KetQuaFile kqSV = docVaNapSinhVienAVL(fileSinhVien, rootAVL);
    if (!kqSV.thanhCong) {
        return kqSV;
    }

    KetQuaFile kqHP = docVaGanHocPhanAVL(fileHocPhan, rootAVL);
    KetQuaFile tongHop;
    tongHop.thanhCong = kqHP.thanhCong;
    tongHop.soDongHopLe = kqSV.soDongHopLe + kqHP.soDongHopLe;
    tongHop.soDongLoi = kqSV.soDongLoi + kqHP.soDongLoi;
    tongHop.thongBao = kqSV.thongBao + " | " + kqHP.thongBao;
    return tongHop;
}

KetQuaFile napDuLieuTongHopBST(const string& fileSinhVien,
                                const string& fileHocPhan,
                                BSTNode*& rootBST) {
    KetQuaFile kq;
    ifstream ifsSV(fileSinhVien);
    if (!ifsSV.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the mo file sinh vien cho BST: " + fileSinhVien;
        return kq;
    }

    string line;
    while (getline(ifsSV, line)) {
        string cleanLine = loaiBoKyTuXuongDong(line);
        if (catKhoangTrangHaiDau(cleanLine).empty()) {
            continue;
        }

        int soPhanTu = 0;
        string* parts = tachTheoDauGachDung(cleanLine, soPhanTu);
        if (parts == nullptr || soPhanTu != 4) {
            giaiPhongMangString(parts);
            ++kq.soDongLoi;
            continue;
        }

        SinhVien sv = taoSinhVien(
            catKhoangTrangHaiDau(parts[0]),
            catKhoangTrangHaiDau(parts[1]),
            catKhoangTrangHaiDau(parts[2]),
            catKhoangTrangHaiDau(parts[3])
        );
        giaiPhongMangString(parts);

        bool chenThanhCong = false;
        rootBST = insertBST(rootBST, sv, chenThanhCong);
        giaiPhongSinhVien(sv);

        if (chenThanhCong) {
            ++kq.soDongHopLe;
        } else {
            ++kq.soDongLoi;
        }
    }
    ifsSV.close();

    ifstream ifsHP(fileHocPhan);
    if (!ifsHP.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the mo file hoc phan cho BST: " + fileHocPhan;
        return kq;
    }

    while (getline(ifsHP, line)) {
        string cleanLine = loaiBoKyTuXuongDong(line);
        if (catKhoangTrangHaiDau(cleanLine).empty()) {
            continue;
        }

        int soPhanTu = 0;
        string* parts = tachTheoDauGachDung(cleanLine, soPhanTu);
        if (parts == nullptr || soPhanTu != 5) {
            giaiPhongMangString(parts);
            ++kq.soDongLoi;
            continue;
        }

        string mssv = catKhoangTrangHaiDau(parts[0]);
        string maHP = catKhoangTrangHaiDau(parts[1]);
        string tenHP = catKhoangTrangHaiDau(parts[2]);
        int soTinChi = 0;
        float diemHe10 = 0.0f;

        bool hopLeSo = parseSoNguyenAnToan(parts[3], soTinChi) &&
                       parseSoThucFloatAnToan(parts[4], diemHe10);
        giaiPhongMangString(parts);

        if (!hopLeSo) {
            ++kq.soDongLoi;
            continue;
        }

        HocPhan* hpMoi = taoHocPhan(maHP, tenHP, soTinChi, diemHe10);
        if (hpMoi == nullptr) {
            ++kq.soDongLoi;
            continue;
        }

        BSTNode* svNode = searchBST(rootBST, mssv);
        if (svNode == nullptr) {
            delete hpMoi;
            ++kq.soDongLoi;
            continue;
        }

        themHocPhan(svNode->data.dsHocPhan, hpMoi);
        ++kq.soDongHopLe;
    }
    ifsHP.close();

    kq.thanhCong = true;
    kq.thongBao = "Nap BST xong (" + to_string(kq.soDongHopLe) +
                  " hop le, " + to_string(kq.soDongLoi) + " dong loi/trung).";
    return kq;
}

KetQuaFile ghiDuLieuRaFileAVL(AVLNode* rootAVL,
                              const string& fileSinhVien,
                              const string& fileHocPhan) {
    KetQuaFile kq;
    ofstream ofsSV(fileSinhVien);
    if (!ofsSV.is_open()) {
        kq.thanhCong = false;
        kq.thongBao = "Khong the ghi file sinh vien: " + fileSinhVien;
        return kq;
    }

    ofstream ofsHP(fileHocPhan);
    if (!ofsHP.is_open()) {
        ofsSV.close();
        kq.thanhCong = false;
        kq.thongBao = "Khong the ghi file hoc phan: " + fileHocPhan;
        return kq;
    }

    int tongSV = 0;
    int tongHP = 0;
    ghiDeQuyAVL(rootAVL, ofsSV, ofsHP, tongSV, tongHP);

    ofsSV.close();
    ofsHP.close();

    kq.thanhCong = true;
    kq.soDongHopLe = tongSV + tongHP;
    kq.thongBao = "Da ghi " + to_string(tongSV) + " sinh vien va " +
                  to_string(tongHP) + " hoc phan ra file.";
    return kq;
}