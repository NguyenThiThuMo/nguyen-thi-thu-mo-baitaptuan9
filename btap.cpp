#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====== CẤU TRÚC ======
struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh; // 1: Nam, 0: Nu
    struct Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    struct SinhVien data;
    struct Node* next;
};

struct List {
    struct Node* head;
};

// ====== KHỞI TẠO ======
void init(struct List* L) {
    L->head = NULL;
}

// ====== XÓA \n ======
void xoaXuongDong(char* s) {
    s[strcspn(s, "\n")] = '\0';
}

// ====== SO SÁNH NGÀY ======
int cungNgay(struct Ngay a, struct Ngay b) {
    return (a.ngay == b.ngay && a.thang == b.thang && a.nam == b.nam);
}

// ====== NHẬP SINH VIÊN ======
struct SinhVien nhapSV() {
    struct SinhVien sv;

    getchar(); // clear buffer

    printf("Ma SV: ");
    fgets(sv.maSV, sizeof(sv.maSV), stdin);
    xoaXuongDong(sv.maSV);

    printf("Ho ten: ");
    fgets(sv.hoTen, sizeof(sv.hoTen), stdin);
    xoaXuongDong(sv.hoTen);

    printf("Gioi tinh (1-Nam, 0-Nu): ");
    scanf("%d", &sv.gioiTinh);

    printf("Ngay sinh (ngay thang nam): ");
    scanf("%d %d %d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);

    getchar();

    printf("Dia chi: ");
    fgets(sv.diaChi, sizeof(sv.diaChi), stdin);
    xoaXuongDong(sv.diaChi);

    printf("Lop: ");
    fgets(sv.lop, sizeof(sv.lop), stdin);
    xoaXuongDong(sv.lop);

    printf("Khoa: ");
    fgets(sv.khoa, sizeof(sv.khoa), stdin);
    xoaXuongDong(sv.khoa);

    return sv;
}

// ====== THÊM CÓ SẮP XẾP ======
void insertSorted(struct List* L, struct SinhVien sv) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        return;
    }

    newNode->data = sv;
    newNode->next = NULL;

    // chèn đầu
    if (L->head == NULL || strcmp(sv.maSV, L->head->data.maSV) < 0) {
        newNode->next = L->head;
        L->head = newNode;
        return;
    }

    // tìm vị trí
    struct Node* p = L->head;
    while (p->next != NULL && strcmp(p->next->data.maSV, sv.maSV) < 0) {
        p = p->next;
    }

    newNode->next = p->next;
    p->next = newNode;
}

// ====== IN DANH SÁCH ======
void inDS(struct List L) {
    struct Node* p = L.head;
    while (p != NULL) {
        printf("[%s] %s\n", p->data.maSV, p->data.hoTen);
        p = p->next;
    }
}

// ====== IN SV TRÙNG NGÀY SINH ======
void inTrungNgay(struct List L) {
    struct Node* p = L.head;
    int found = 0;

    while (p != NULL) {
        struct Node* q = p->next;
        while (q != NULL) {
            if (cungNgay(p->data.ngaySinh, q->data.ngaySinh)) {
                printf("%s va %s trung ngay sinh\n",
                    p->data.hoTen, q->data.hoTen);
                found = 1;
            }
            q = q->next;
        }
        p = p->next;
    }

    if (!found)
        printf("Khong co SV trung ngay sinh\n");
}

// ====== XÓA SV TRÙNG NGÀY SINH (giữ lại 1) ======
void xoaTrungNgay(struct List* L) {
    struct Node* p = L->head;

    while (p != NULL) {
        struct Node* prev = p;
        struct Node* q = p->next;

        while (q != NULL) {
            if (cungNgay(p->data.ngaySinh, q->data.ngaySinh)) {
                prev->next = q->next;
                free(q);
                q = prev->next;
            }
            else {
                prev = q;
                q = q->next;
            }
        }
        p = p->next;
    }
}

// ====== MAIN ======
int main() {
    struct List ds;
    init(&ds);

    int n;
    printf("Nhap so SV: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nNhap SV thu %d:\n", i + 1);
        struct SinhVien sv = nhapSV();
        insertSorted(&ds, sv);
    }

    printf("\n--- Danh sach ---\n");
    inDS(ds);

    printf("\n--- SV trung ngay sinh ---\n");
    inTrungNgay(ds);

    printf("\n--- Sau khi xoa ---\n");
    xoaTrungNgay(&ds);
    inDS(ds);

    return 0;
}