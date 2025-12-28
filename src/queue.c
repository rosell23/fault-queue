#ifndef _FQ_QUEUE_H_
#define _FQ_QUEUE_H_	1

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAXFAULTS	16

typedef struct queue {
	size_t items[MAXFAULTS];
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
enqueue(Queue* q, uint8_t val) {
	if (q->front == -1)
		q->front = 0; /* start queue */

	if (isfull(q)) {
#	ifdef	FQ_VERBDEBUG
		puts("fq [verbdebug] - enqueuing full list, wrapping...");
#	endif
		q->front = 0;
		q->rear = MAXFAULTS;
	}

	q->rear++;
	q->items[q->rear] = val;
#	ifdef FQ_VERBDEBUG
	printf("fq [verbdebug] - enqueued item #%s -> x%x\n.", q->rear, val);
#	endif
}

void
dequeue(Queue* q) {
	if (isempty(q)) {
		
	}
}

#endif /* _FQ_QUEUE_H_ */
