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