#ifndef _FQ_INTERNAL_QUEUE_H_
#define _FQ_INTERNAL_QUEUE_H_	1

#include "fault.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
	extern "C" {
#endif

#define MAXFAULTS	16

typedef struct queue {
	Fault* items[MAXFAULTS];
	int8_t front, rear;
} Queue;

#ifdef __cplusplus
	}
#endif

#endif /* _FQ_INTERNAL_QUEUE_H_ */
