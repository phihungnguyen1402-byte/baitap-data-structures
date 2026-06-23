#include <stdio.h>
#include <assert.h>
#include "mempool.h"

void test_MemPool() {
    MemPool_t pool;
    MemPool_Init(&pool);
    
    // Tạo một mảng con trỏ để giữ "chìa khóa" của 5 chiếc xe
    void* ptrs[POOL_SIZE];
    
    printf("[1] Xin cap phat kin 5 cho dau xe...\n");
    for (int i = 0; i < POOL_SIZE; i++) {
        ptrs[i] = MemPool_Alloc(&pool);
        // Kiểm tra: Bắt buộc phải có chỗ (con trỏ khác NULL)
        assert(ptrs[i] != NULL); 
    }
    
    printf("[2] Co tinh xin them block thu 6 khi bai da day...\n");
    void* extraPtr = MemPool_Alloc(&pool);
    // Kiểm tra: Bắt buộc phải bị từ chối (trả về NULL, không bị crash hệ thống)
    assert(extraPtr == NULL);
    
    printf("[3] Tra lai block so 3 (index 2) de tao khoang trong...\n");
    // Kiểm tra: Hàm Free phải báo thành công
    assert(MemPool_Free(&pool, ptrs[2]) == true);
    
    printf("[4] Cố tinh tra lai mot dia chi tao lao khong thuoc bai...\n");
    int fakeData = 999;
    // Kiểm tra: Hàm Free phải từ chối nhận vì địa chỉ lạ
    assert(MemPool_Free(&pool, &fakeData) == false);
    
    printf("[5] Xin cap phat lai 1 block moi...\n");
    void* newPtr = MemPool_Alloc(&pool);
    // Kiểm tra 1: Phải cấp phát thành công
    assert(newPtr != NULL);
    // Kiểm tra 2: Chỗ mới được cấp phải trùng khớp chính xác vào chỗ số 3 vừa bị trống lúc nãy
    assert(newPtr == ptrs[2]);
}

int main() {
    printf("=== KHOI DONG UNIT TEST MEMORY POOL ===\n");
    
    test_MemPool();
    
    printf("\n=> TUDUY CHUAN: TAT CA CAC TEST MEMORY POOL DEU PASS 100%%!\n");
    return 0;
}