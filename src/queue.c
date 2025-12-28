#ifndef _FQ_QUEUE_H_
#define _FQ_QUEUE_H_	1

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <fq/faults-builtin.h>
#include <fq/fault.h>

#define MAXFAULTS	16

typedef struct queue {
	Fault* items[MAXFAULTS];
	int8_t front, rear;
} Queue;

void
mkqueue(Queue* q) {
	q->front = -1;
	q->rear  = -1;
}

bool
isfull(Queue* q) {
	return (q->rear == MAXFAULTS - 1);
}

bool
isempty(Queue* q) {
	return (q->front == -1 || q->front > q->rear);
}

void
enqueue(Queue* q, Fault* val) {
	if (q->front == -1)
		q->front = 0; /* start queue */

	if (isfull(q)) {
#	ifdef	FQ_VERBDEBUG
		puts("fq [verbdebug] - enqueuing full list, wrapping...");
#	endif
		q->front = 0;
		q->rear = -1;
	}

	q->rear++;
	q->items[q->rear] = val;
#	ifdef FQ_VERBDEBUG
	printf("fq [verbdebug] - enqueued item #%s -> x%x\n.", q->rear, val);
#	endif
}

Fault*
dequeue(Queue* q) {
	if (isempty(q)) {
#	ifdef FQ_VERBDEBUG
		printf("fq [verbdebug] - can't dequeue empty list\n");
#	endif
		enqueue(q, FQUEUE);
		return FQUEUE;
	}

	Fault* value = q->items[q->front];
	q->front++;
	if (q->front > q->rear) { /* reset queue if it becomes void */
		q->front = q->rear = -1;
	}

	return value;
}

Fault*
firstf(Queue* q) {
	if (isempty(q)) {
#	ifdef FQ_VERBDEBUG
		puts("fq [verbdebug] - can't get first fault from an empty fault-queue");
#	endif
		enqueue(q, FQUEUE);
		return FQUEUE;
	}

	return q->items[q->front];
}

#endif /* _FQ_QUEUE_H_ */
