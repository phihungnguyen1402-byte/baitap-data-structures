#include <stdio.h>

// 1. Định nghĩa các trạng thái bằng enum cho dễ quản lý (giá trị tự động là 0, 1, 2, 3)
typedef enum {
    STATE_IDLE = 0,
    STATE_RUN,
    STATE_SPRAY,
    STATE_ERROR
} AGV_State_t;

// 2. Các hàm xử lý thực tế cho từng trạng thái
void State_Idle() { 
    printf("[AGV] Cho lenh tu Jetson Orin...\n"); 
}
void State_Run() { 
    printf("[AGV] 4 banh dang quay, tien vao luong cay...\n"); 
}
void State_Spray() { 
    printf("[AGV] Phat hien cay benh -> Kich hoat may bom xit thuoc!\n"); 
}
void State_Error() { 
    printf("[AGV] CANH BAO: Loi phan cung! Dung khan cap!\n"); 
}

int main() {
    // 3. BÍ QUYẾT: Khai báo mảng con trỏ hàm
    // Lưu ý: Thứ tự các hàm truyền vào mảng phải KHỚP TÍNH CHÍNH XÁC với thứ tự của enum ở trên
    void (*StateMachine[])(void) = {
        State_Idle,  // Nằm ở vị trí 0 (STATE_IDLE)
        State_Run,   // Nằm ở vị trí 1 (STATE_RUN)
        State_Spray, // Nằm ở vị trí 2 (STATE_SPRAY)
        State_Error  // Nằm ở vị trí 3 (STATE_ERROR)
    };

    printf("--- MO PHONG HE THONG FSM CHO AGV ---\n\n");

    // Giả lập quá trình hoạt động của AGV
    AGV_State_t currentState = STATE_IDLE;
    
    // Gọi hàm chạy ngay lập tức bằng index, KHÔNG CẦN IF-ELSE hay SWITCH-CASE!
    StateMachine[currentState](); 

    printf("\n--> Nhan lenh bat dau di chuyen...\n");
    currentState = STATE_RUN;
    StateMachine[currentState]();

    printf("\n--> Camera nhan dien co sau benh...\n");
    currentState = STATE_SPRAY;
    StateMachine[currentState]();

    printf("\n--> Cam bien va cham phat hien da tang...\n");
    currentState = STATE_ERROR;
    StateMachine[currentState]();

    return 0;
}