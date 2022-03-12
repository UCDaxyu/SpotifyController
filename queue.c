#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"

#define QUEUE_CAPACITY 50
#define QUEUE_CAPACITY_MULTIPLIER 2
/*
struct queue_node{
	void *data;
	struct queue_node *next_node = NULL;
	struct queue_node *prev_node = NULL;
}
*/

struct s_queue {
	unsigned int data[QUEUE_CAPACITY];
	short unsigned int tap_count[QUEUE_CAPACITY];
	int size; 
	int capacity;
	int head;
	int tail;
} queue;

queue_t queue_create(void){
	queue_t new_queue = (queue_t)malloc(sizeof(queue));

	new_queue->head = 0;
	new_queue->tail = 0;
	new_queue->size = 0;
	new_queue->capacity = QUEUE_CAPACITY;
	//new_queue->data;
	return new_queue;
}

int queue_destroy(queue_t queue){
	if(queue == NULL || queue->size == 0)
		return -1;
	free(queue->data);
	free(queue);
	queue = NULL;
	return 0;
}

int queue_enqueue(queue_t queue, unsigned int data, short unsigned int cur_tap_count){
	if(queue->size == queue->capacity){
		return -1;
	}
	queue->data[queue->tail] = data;
	queue->tap_count[queue->tail] = cur_tap_count;

	if(queue->size >= queue->capacity){
		return -1;
	}
	else{
		queue->size++;
	}
	if(queue->tail == queue->capacity - 1){
		queue->tail = 0;
	}else{
		queue->tail++;
	}


	return 0;
}

int queue_dequeue(queue_t queue, unsigned int *data, short unsigned int *count){
	if (queue->head == -1 || queue->size == 0){
	//if (queue->head == NULL || queue->size == 0){
		return -1;
	}

	*data = queue->data[queue->head];
	*count = queue->tap_count[queue->head];
	queue->size--;
	queue->head++;
	if(queue->head == queue->capacity){
		queue->head = 0;
	}

	return 0;
}

int queue_length(queue_t queue){
	if (queue->head < 0 ){
		return -1;
	}
	return queue->size;
}
