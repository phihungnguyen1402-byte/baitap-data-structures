#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define BLOCK_SIZE 32  // Kích thước mỗi khối (ví dụ 32 bytes/khối)
#define POOL_SIZE 5    // Tổng số khối có trong bãi (có 5 chỗ đậu xe)

typedef struct {
    // Mảng 2 chiều chứa dữ liệu thực tế (5 khối, mỗi khối 32 byte)
    uint8_t blocks[POOL_SIZE][BLOCK_SIZE]; 
    
    // Mảng cờ để đánh dấu: true là đang rảnh, false là đang có người dùng
    bool isFree[POOL_SIZE];                
} MemPool_t;

// Các hàm quản lý bãi đậu xe
void MemPool_Init(MemPool_t* pool);
void* MemPool_Alloc(MemPool_t* pool);           // Xin cấp phát (thay cho malloc)
bool MemPool_Free(MemPool_t* pool, void* ptr);  // Trả lại (thay cho free)

#endif // MEMPOOL_H