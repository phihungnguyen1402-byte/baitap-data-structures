#include <stdlib.h> // Thư viện bắt buộc để dùng hàm cấp phát bộ nhớ malloc
#include <stdio.h>  // Thư viện để dùng hàm printf
#include "linkedlist.h"

// Khởi tạo đoàn tàu rỗng
void LinkedList_Init(LinkedList_t* list) {
    list->head = NULL;
}

// Hàm tạo toa tàu mới và móc vào ĐUÔI
bool LinkedList_InsertTail(LinkedList_t* list, uint8_t data) {
    // 1. Xin hệ điều hành (RAM) cấp cho một khoảng trống vừa bằng 1 cái Node
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    
    // 2. Kiểm tra xem RAM có bị đầy không (Rất quan trọng)
    if (newNode == NULL) {
        return false; // Hết RAM, tạo thất bại
    }
    
    // 3. Đưa dữ liệu vào toa mới, và chốt cái móc của toa này lại (trỏ vào NULL)
    newNode->data = data;
    newNode->next = NULL;
    
    // 4. Tìm cách móc toa mới này vào đoàn tàu hiện tại
    if (list->head == NULL) {
        // TRƯỜNG HỢP A: Đoàn tàu chưa có toa nào
        // -> Cho toa mới này làm Đầu Tàu luôn
        list->head = newNode;
    } else {
        // TRƯỜNG HỢP B: Đã có tàu rồi. Phải đi bộ từ đầu tàu xuống cuối tàu để móc
        Node_t* current = list->head; // Bắt đầu đi từ toa đầu
        
        // Vòng lặp: Chừng nào toa hiện tại VẪN CÒN móc nối với toa khác, thì cứ đi tiếp
        while (current->next != NULL) {
            current = current->next; // Bước sang toa tiếp theo
        }
        
        // Thoát khỏi vòng lặp tức là đang đứng ở toa cuối cùng. Móc toa mới vào thôi!
        current->next = newNode;
    }
    
    return true; // Thêm thành công
}

// Hàm in đoàn tàu ra màn hình để kiểm tra bằng mắt
void LinkedList_Print(LinkedList_t* list) {
    printf("Doan tau: ");
    Node_t* current = list->head;
    
    while (current != NULL) {
        printf("[%d] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
// Hàm tìm kiếm xem một số có nằm trên đoàn tàu không
bool LinkedList_Find(LinkedList_t* list, uint8_t target) {
    Node_t* current = list->head;
    
    while (current != NULL) {
        if (current->data == target) {
            return true; // Tìm thấy!
        }
        current = current->next; // Đi sang toa tiếp theo
    }
    return false; // Đi hết tàu mà không thấy
}

// Hàm cắt bỏ toa đầu tiên và lấy hàng hóa ra
bool LinkedList_RemoveHead(LinkedList_t* list, uint8_t* outData) {
    // 1. Kiểm tra tàu có rỗng không
    if (list->head == NULL) {
        return false; 
    }
    
    // 2. Chốt vị trí toa đầu tiên hiện tại
    Node_t* nodeToRemove = list->head;
    
    // 3. Lấy dữ liệu ra đưa cho khách hàng
    *outData = nodeToRemove->data;
    
    // 4. Dời vị trí "Đầu tàu" sang toa thứ 2
    list->head = nodeToRemove->next;
    
    // 5. QUAN TRỌNG NHẤT: Phá hủy toa cũ, trả lại RAM!
    free(nodeToRemove);
    
    return true; // Xóa thành công
}