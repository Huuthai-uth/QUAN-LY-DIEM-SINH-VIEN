#ifndef AVL_H
#define AVL_H
#include "SinhVien.h"

using namespace std;

struct NodeAVL{
    SinhVien data;
    NodeAVL* left;
    NodeAVL* right;
    int height;
    NodeAVL(const SinhVien& sv);
};

struct CayAVL{
    NodeAVL* root;
    int soLuong;

    CayAVL();
};
void KhoiTaoCay(CayAVL& cay);
void GiaiPhongCay(CayAVL& cay);
int ChieuCao(const NodeAVL* node);
void CapNhatChieuCao(NodeAVL* node);
int HeSoCanBang(const NodeAVL* node);
NodeAVL* XoayPhai(NodeAVL* y);          
NodeAVL* XoayTrai(NodeAVL* x);          
NodeAVL* CanBang(NodeAVL* node);       
bool ThemSinhVien(CayAVL& cay, const SinhVien& sv);
bool XoaSinhVien(CayAVL& cay, const string& mssv);
NodeAVL* TimSinhVien(CayAVL& cay, const string& mssv);
const NodeAVL* TimSinhVien(const CayAVL& cay, const string& mssv);
void DuyetLNR(const CayAVL& cay);
void DuyetNLR(const CayAVL& cay);
void DuyetLRN(const CayAVL& cay);
void InCayDangCay(const CayAVL& cay);
bool KiemTraCayAVL(const CayAVL& cay);
bool KiemThuCanBang();

#endif
