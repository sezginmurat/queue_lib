#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 * queue structure.
 */
struct queue {
	struct node *head;
	struct node *tail;
	int size;
};

/*
 * queue_print()
 *	Prints the queue elements.
 */
void queue_print(struct queue *q)
{
	if (!q) {
		printf("queue is null, cannot print\n");
		return;
	}

	if (!q->head) {
		printf("queue is empty, cannot print anything\n");
		return;
	}

	struct node *n = q->head;
	while (n) {
		printf("%d->", n->data);
		n = n->next;
	}

	printf("null\n");
	
}

/*
 * queue_add_head()
 *	Adds a data at the head of the queue.
 */
void queue_add_head(struct queue *q, int data)
{
	if (!q) {
		printf("queue is null, cannot add head\n");
		return;
	}

	struct node *n = node_create(data);
	if (!n) {
		printf("failed to create node\n");
		return;
	}

	if (!q->head) {
		q->head = n;
		q->tail = n;
		return;
	}

	n->next = q->head;
	q->head = n;

	q->size++;	 
}

/*
 * queue_enqueue()
 *	Enqueues a data to the queue.
 */
void queue_enqueue(struct queue *q, int data)
{
	if (!q) {
		printf("queue is null, cannot add tail\n");
		return;
	}

	struct node *n = node_create(data);
	if (!n) {
		printf("failed to create node\n");
		return;
	}

	if (!q->tail) {
		q->tail = n;
		q->head = n;
		return;
	}

	q->tail->next = n;
	q->tail = n;

	q->size++;	 
}

/*
 * queue_dequeue()
 *	Dequeues a data from the queue.
 */
struct node *queue_dequeue(struct queue *q)
{
	if (!q) {
		printf("queue is null, cannot dequeue\n");
		return NULL;
	}

	if (!q->head) {
		printf("q head is null, q is empty, cannot dequeue\n");
		return NULL;
	}

	struct node *n = q->head;
	q->head = q->head->next;
	if (!q->head) {
		q->tail = NULL;
	}

	q->size--;

	return n;
}

/*
 * queue_delete()
 *	Deletes a queue.
 */
void queue_delete(struct queue **q)
{
	if (!*q) {
		printf("queue is null, cannot delete\n");
		return;
	}

	struct node *n = queue_dequeue(*q);
	while (n) {
		node_free(n);
		n = queue_dequeue(*q);
	}

	free(*q);
	*q = NULL;
}

/*
 * queue_create()
 *	Creates an empty queue.
 */
struct queue *queue_create(void)
{
	struct queue *q = malloc(sizeof(struct queue));
	if (!q) {
		printf("Failed to alloc memory for q\n");
		return NULL;
	}

	q->head = q->tail = NULL;
	q->size = 0;

	return q;
}

/*
 * Test code.
 */
int main(void)
{
	struct queue *q = queue_create();
	if (!q) {
		printf("Failed to create queue\n");
		return 1;
	}

	/*
	 * 4->3->2->1->5->6->7->8->null
	 */
	queue_enqueue(q, 1);
	queue_enqueue(q, 2);
	queue_enqueue(q, 3);
	queue_enqueue(q, 4);
	queue_enqueue(q, 5);
	queue_enqueue(q, 6);
	queue_enqueue(q, 7);
	queue_enqueue(q, 8);

	queue_print(q);

	for (int i = 0; i < 8; i++) {
		struct node *n = queue_dequeue(q);
		if (n) {
			printf("n->data: %d\n", n->data);
			node_free(n);
		}
	}

	queue_print(q);
	queue_delete(&q);
	queue_print(q);
	queue_delete(&q);
	return 0;
}
