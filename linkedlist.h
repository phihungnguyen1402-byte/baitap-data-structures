#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // Để dùng chữ NULL


typedef struct Node {
    uint8_t data;           // Hàng hóa: Chứa 1 byte dữ liệu
    struct Node* next;      // Cái móc: Con trỏ trỏ đến toa tàu tiếp theo
} Node_t;

typedef struct {
    Node_t* head;           // Con trỏ trỏ đến toa đầu tiên của đoàn tàu
} LinkedList_t;

// Các hàm cơ bản sẽ làm
void LinkedList_Init(LinkedList_t* list);
bool LinkedList_InsertTail(LinkedList_t* list, uint8_t data); // Thêm vào đuôi
void LinkedList_Print(LinkedList_t* list);                    // In ra để xem
bool LinkedList_RemoveHead(LinkedList_t* list, uint8_t* outData); // Xóa toa đầu
bool LinkedList_Find(LinkedList_t* list, uint8_t target);         // Tìm hàng hóa
#endif // LINKEDLIST_H