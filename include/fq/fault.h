#ifndef _FQ_FAULT_H_
#define _FQ_FAULT_H_	1

#include <stdint.h>

#ifdef __cplusplus
	extern "C" {
#endif

typedef	void (*faultcb)(void);
	
typedef struct fault {
	uint8_t	id;
	faultcb	callback;
} Fault;

#ifdef __cplusplis
	}
#endif

#endif /* _FQ_FAULT_H_ */

