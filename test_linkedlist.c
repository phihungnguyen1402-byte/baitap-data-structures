#include <stdio.h>
#include <assert.h>
#include "linkedlist.h"

void test_LinkedList() {
    LinkedList_t list;
    LinkedList_Init(&list);
    uint8_t data;

    // 1. Test Thêm dữ liệu (Insert)
    assert(LinkedList_InsertTail(&list, 10) == true);
    assert(LinkedList_InsertTail(&list, 20) == true);
    assert(LinkedList_InsertTail(&list, 30) == true);

    // 2. Test Tìm kiếm (Find)
    assert(LinkedList_Find(&list, 20) == true);   // Số 20 phải có trên tàu
    assert(LinkedList_Find(&list, 99) == false);  // Số 99 không được có trên tàu

    // 3. Test Xóa dữ liệu (RemoveHead)
    // Do mình thêm vào đuôi (10 -> 20 -> 30), nên khi xóa từ đầu, 
    // thứ tự lấy ra phải đúng chuẩn FIFO là 10, rồi 20, rồi 30.
    assert(LinkedList_RemoveHead(&list, &data) == true);
    assert(data == 10);

    assert(LinkedList_RemoveHead(&list, &data) == true);
    assert(data == 20);

    assert(LinkedList_RemoveHead(&list, &data) == true);
    assert(data == 30);

    // 4. Lúc này tàu đã bị tháo hết toa, nếu cố tình xóa tiếp phải trả về false
    assert(LinkedList_RemoveHead(&list, &data) == false);
}

int main() {
    printf("=== KHOI DONG UNIT TEST LINKED LIST ===\n");
    
    test_LinkedList();
    
    printf("\n=> TUDUY CHUAN: TAT CA CAC TEST LINKED LIST DEU PASS 100%%!\n");
    return 0;
}