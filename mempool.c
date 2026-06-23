#include "mempool.h"

// 1. Khởi tạo: Ban đầu tất cả đều trống
void MemPool_Init(MemPool_t* pool) {
    for (int i = 0; i < POOL_SIZE; i++) {
        pool->isFree[i] = true; 
    }
}

// 2. Xin cấp phát một khối bộ nhớ
// Trả về con trỏ (void*) trỏ tới khối đó, nếu hết chỗ thì trả về NULL
void* MemPool_Alloc(MemPool_t* pool) {
    for (int i = 0; i < POOL_SIZE; i++) {
        if (pool->isFree[i] == true) {
            pool->isFree[i] = false; // Đánh dấu là đã có người xài
            return pool->blocks[i];  // Giao chìa khóa (địa chỉ của khối) cho khách
        }
    }
    return NULL; 
}

// 3. Trả lại khối bộ nhớ khi không dùng nữa
bool MemPool_Free(MemPool_t* pool, void* ptr) {
    if (ptr == NULL) return false;

    // Quét xem cái địa chỉ (ptr) khách trả lại nó nằm ở vị trí nào trong bãi
    for (int i = 0; i < POOL_SIZE; i++) {
        if (ptr == pool->blocks[i]) {
            pool->isFree[i] = true; // Đánh dấu là chỗ này lại trống
            return true;
        }
    }
    return false; 
}