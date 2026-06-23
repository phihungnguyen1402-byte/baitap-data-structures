#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 10

// Đưa định nghĩa Struct ra đây
typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
    bool isFull;
} RingBuffer_t;

// Chỉ để lại "cái vỏ" của các hàm (Function Prototypes)
void RingBuffer_Init(RingBuffer_t *rb);
bool RingBuffer_Write(RingBuffer_t *rb, uint8_t data);
bool RingBuffer_Read(RingBuffer_t *rb, uint8_t *data);
bool RingBuffer_ReadUntil(RingBuffer_t *rb, uint8_t *outBuffer, uint8_t stopChar);
#endif // RINGBUFFER_H