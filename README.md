fault-queue - better error handling in C
========================================

> fault-queue (fq) is a C utility mini-library that improves error handling.

Pretext
-------

C has traditionally always used the global `errno` and sentinel values for
error handling, which makes for a totally awful and inconsistent experience.

fault-queue fixes this by providing a, well, queue, of incoming _faults_
with specific IDs that can be separately handled and don't clutter error codes.

Features
--------

fq is intentionally _very_ minimalistic:

* `errno` integration
* simple, enjoyable API
* some utilities.
* readable

Building
--------

fq uses plain Ninja for building, just do:

~~~sh
$ ninja
< a bunch of stuff >
~~~

It should generate `fq.a` (a static library).

Examples
--------

Here's an example of a simple function that fetches a server's IP from its URL:

~~~c
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include <fq.h>

NEWFAULT(FNOHOST);

static
FQTYPE(const char*, FNOHOST)
getip(const char* host) {
	struct hostent* lh = gethostbyname(host);

	if (!lh)
		RAISE(FNOHOST);

	return (lh->h_name);
}

int
main(int argc, char* argv[]) {
	LCONNECT(FNOHOST, {
		herror("get host");
		return (EXIT_FAILURE); });

	return (EXIT_SUCCESS);
}
~~~

(Albeit, this example isn't the best, since `getip()` returns an string, but it is enough for demonstration.)

Known Issues/Limitations
------------------------

* Can't connect to multiple faults in a single line.
* The entire library is **_very_ thread-unsafe**

Reference
---------

Refer to <doc/reference.md> for more information.

Licensing
---------

Public domain, because
[so called "intellectual property" is much of an oxymoron](https://harmful.cat-v.org/economics/intellectual_property/).

If you prefer it, or your country's patent protection and copyright department is ran by
braindead retards that won't accept PD, you can use (CC0's fallback or) the ISC license instead.

