#ifndef _FQ_BUILTIN_FAULTS_H_
#define _FQ_BUILTIN_FAULTS_H_	1

#include <fq/fault.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
	extern "C" {
#endif
	
static Fault queue_fault = {.id = 0x01, .callback = NULL};
Fault* const FQUEUE = &queue_fault;

/* "highest" fault */
const uint8_t lastqueue = 0x01;

#ifdef __cplusplus
	}
#endif

#endif /* _FQ_BUILTIN_FAULTS_H_ */

