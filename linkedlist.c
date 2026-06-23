#include <stdlib.h> 
#include <stdio.h>  
#include "linkedlist.h"
void LinkedList_Init(LinkedList_t* list) {
    list->head = NULL;
}
bool LinkedList_InsertTail(LinkedList_t* list, uint8_t data) {
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    if (newNode == NULL) {
        return false; // Hết RAM, tạo thất bại
    }
    newNode->data = data;
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node_t* current = list->head; 
        while (current->next != NULL) {
            current = current->next; 
        }
        current->next = newNode;
    }
    return true;    
}
void LinkedList_Print(LinkedList_t* list) {
    printf("Doan tau: ");
    Node_t* current = list->head;
    while (current != NULL) {
        printf("[%d] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
bool LinkedList_Find(LinkedList_t* list, uint8_t target) {
    Node_t* current = list->head;
    
    while (current != NULL) {
        if (current->data == target) {
            return true; 
        }
        current = current->next; 
    }
    return false; 
}
bool LinkedList_RemoveHead(LinkedList_t* list, uint8_t* outData) {
    if (list->head == NULL) {
        return false; 
    }
    Node_t* nodeToRemove = list->head;
    *outData = nodeToRemove->data;
    list->head = nodeToRemove->next;
    free(nodeToRemove);
    return true; 
}