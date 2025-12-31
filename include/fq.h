#ifndef _FQ_H_
#define _FQ_H_	1

#include <stddef.h>
#include "fq/queue.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*
 * fq.h --- user header: includes and macros
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *
 * User-facing header, includes everything and does some macro wizardy
 */

#include "fq/fault.h"
#include "fq/faults-builtin.h"
#include "fq/queue.h"

/* define `forced'-assertation, since C won't make asserts work without debug mode */
#if __STDC_VERSION__ >= 201112L	 /* C11 and later have _Static_assert for this */
#	define STATIC_ASSERT(what, msg) \
		_Static_assert(what, msg)
#else  /* Old-school C89/C90/C99. If what is false (0), then division by zero happens.
	* Note: this is unreadable.
	* Note[2]: since some idiots define true as masks or -1 rather than 1,
	*	some stuff makes no sense (what? 1 : 0 for example)
	* Example:
	* 	STATIC_ASSERT(sizeof(int) == 4, int_shall_be_4_bits)*/
#       define DUCKTAPE(a, b)            a##b /* joins a and b */
#       define MOREDUCKTAPE(a, b)    DUCKTAPE(a, b) /* joins a and b too */
#       if __STDC_VERSION__ >= 201112L
#           define STATIC_ASSERT(what, msg) _Static_assert(what, msg)
#       else
#           define STATIC_ASSERT(what, msg) \
                enum { MOREDUCKTAPE(static_assert_at, __LINE__) = 1 / ((what) ? 1 : 0) }
#       endif
#endif

/* NOTE: FQTYPE does absolutely nothing, it's just for IDEs */
#define FQTYPE(at, ft)	at

#define CONNECT(e, f)	(e).callback = (f)

/* Make a function and connect to it, L for lambda.
 *
 * IMPLEMENTATION NOTE: the C preprocessor doesn't expand newlines on any
 * compiler/preprocessor. */
#define LCONNECT(e, w) \
    static void __fq_cb_##e(void) { w; } \
    CONNECT(e, __fq_cb_##e)

#define DISCONNECT(w) \
	(w)->callback = NULL;

/* Global queue */
Queue gq;
#define RAISE(f) \
    do { \
        if (gq) { \
            enqueue(gq, &f); \
            (void)(1 / (gq->items[gq->front] == &f ? 1 : 0)); \
        } \
    } while(0)

#ifdef __cplusplus
	}
#endif

#endif /* _FQ_H_ */
