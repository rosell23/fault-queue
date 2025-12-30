#ifndef _FQ_H_
#define _FQ_H_	1

#include <stddef.h>
#include "internal/queue.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*
 * fq.h --- user header: includes and macros
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *
 * User-facing header, includes everything and does some macro wizardy
 */

#include "fq/internal/faults.h"
#include "fq/internal/faults-builtin.h"
#include "fq/internal/queue.h"

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
#	define DUCKTAPE(a, b)		a##b /* joins a and b */
#	define MOREDUCKTAPE(a, b)	DUCKTAPE(a, b) /* joins a and b too */
#	define STATIC_ASSERT(what, msg) \
		enum { MOREDUCKTAPE(static_assert_at, __LINE__) = 1 / ((what)? 1 : 0) }
#endif

/* NOTE: FQTYPE does absolutely nothing, it's just for IDEs */
#define FQTYPE(at, ft)	at

#define CONNECT(e, f)	(##e)->

/* Make a function and connect to it, L for lambda.
 *
 * IMPLEMENTATION NOTE: the C preprocessor doesn't expand newlines on any
 * compiler/preprocessor. */
#define LCONNECT(e, w) \
	void __fq_cb_anon_##__LINE__##__(void) {\
		w;\
	}\
	CONNECT((e), __fq_cb_anon_##__LINE__##__)

#define DISCONNECT(w) \
	(w)->callback = NULL;

/* Global queue */
Queue gq;
#define RAISE(f) \
	enqueue(gq, f);\
	STATIC_ASSERT(gq->items[gq->front] == f);

#ifdef __cplusplus
	}
#endif

#endif /* _FQ_H_ */
