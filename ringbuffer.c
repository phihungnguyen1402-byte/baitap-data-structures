// Bắt buộc phải "nhúng" cái menu vào để nó biết đang làm cho món nào
#include "ringbuffer.h" 

void RingBuffer_Init(RingBuffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->isFull = false;
    for(int i = 0; i < BUFFER_SIZE; i++) {
        rb->buffer[i] = 0;
    }
}

bool RingBuffer_Write(RingBuffer_t *rb, uint8_t data) {
    if (rb->isFull == true) {
        return false; 
    }
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    if (rb->head == rb->tail) {
        rb->isFull = true;
    }
    return true; 
}

bool RingBuffer_Read(RingBuffer_t *rb, uint8_t *data) {
    if (rb->head == rb->tail && rb->isFull == false) {
        return false; 
    }
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    rb->isFull = false;
    return true; 
}

// Hàm đọc liên tục cho đến khi gặp stopChar hoặc kho rỗng
bool RingBuffer_ReadUntil(RingBuffer_t *rb, uint8_t *outBuffer, uint8_t stopChar) {
    int i = 0;
    uint8_t data;

    // Vòng lặp: Chừng nào kho còn đồ để lấy (gọi hàm Read thành công)
    while (RingBuffer_Read(rb, &data) == true) {
        
        // BƯỚC 1: Bỏ byte 'data' vừa gắp được vào mảng 'outBuffer' tại vị trí 'i'
        outBuffer[i] = data;
        
        // BƯỚC 2: Kiểm tra xem 'data' có trúng với 'stopChar' không?
        if (data == stopChar) {
            outBuffer[i + 1] = '\0'; // Chốt đuôi \0 để tạo thành chuỗi String chuẩn C
            return true;             // Báo hiệu đã gắp được một lệnh hoàn chỉnh
        }

        // BƯỚC 3: Tăng 'i' lên 1 bước để chuẩn bị cất byte tiếp theo
        i++;
    }

    // Đọc cạn kiệt kho rồi mà vẫn không thấy stopChar
    outBuffer[i] = '\0'; // Vẫn phải chốt đuôi mảng cho an toàn
    return false;        // Báo hiệu là chưa thu thập đủ một lệnh hoàn chỉnh
}