#include <stdio.h>
#include <assert.h>     // Thu vien dung de Unit Test
#include "ringbuffer.h"

// test cho chức năng Init (Khởi tạo)
void test_RingBuffer_Init() {
    RingBuffer_t rb;
    RingBuffer_Init(&rb);
    
    // assert sẽ kiểm tra điều kiện bên trong ngoặc. 
    // Nếu ĐÚNG -> chạy tiếp. Nếu SAI -> crash chương trình và báo lỗi.
    assert(rb.head == 0);
    assert(rb.tail == 0);
    assert(rb.isFull == false);
    
    printf("PASS: test_RingBuffer_Init\n");
}

//  test cho chức năng Ghi và Đọc
void test_RingBuffer_WriteRead() {
    RingBuffer_t rb;
    RingBuffer_Init(&rb);
    uint8_t outData;

    //  Ghi 1 byte vào phải thành công, và head phải tăng lên 1
    assert(RingBuffer_Write(&rb, 42) == true);
    assert(rb.head == 1);
    
    // Test 2: Đọc ra phải thành công, data gắp ra phải đúng là 42, và tail tăng lên 1
    assert(RingBuffer_Read(&rb, &outData) == true);
    assert(outData == 42);
    assert(rb.tail == 1);
    
    printf("PASS: test_RingBuffer_WriteRead\n");
}

// test kịch bản tràn Buffer (Wrap-around)
void test_RingBuffer_WrapAround() {
    RingBuffer_t rb;
    RingBuffer_Init(&rb);
    
    // Ghi liên tục cho đến khi đầy (BUFFER_SIZE là 10)
    for(int i = 0; i < BUFFER_SIZE; i++) {
        assert(RingBuffer_Write(&rb, i * 10) == true);
    }
    
    // Lúc này cờ isFull phải được bật lên
    assert(rb.isFull == true);
    
    // Cố tình ghi thêm byte thứ 11 -> Phải bị từ chối (trả về false)
    assert(RingBuffer_Write(&rb, 99) == false);
    
    printf("PASS: test_RingBuffer_WrapAround\n");
}

int main() {
    printf("=== KHOI DONG HE THONG UNIT TEST ===\n");
    
    test_RingBuffer_Init();
    test_RingBuffer_WriteRead();
    test_RingBuffer_WrapAround();
    
    printf("\n=> TUDUY CHUAN: TAT CA CAC TEST DEU PASS 100%%!\n");
    return 0;
}