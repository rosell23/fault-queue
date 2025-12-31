For most things, do whatever you want.

## Some _disclaimers_

* You hereby agree to the license by contributing (obviously).

## Style

* Use eight-spaced tabs for indentation.
* Use ISO C99 for the language.
* Keep a newline at the end of the file.
* Keep a newline between a function's type and specifiers.
  * Type specifiers (`static`, `inline`, _et al_) should be on different lines too.
* Use at maximum 90 characters
* Go-to is allowed and encouraged.
* Follow the UNIX-style.
* Use `#include` guards.
* Use [Ninja](https://ninja-build.org/) and [Bazel](https://bazel.build/)
	for building.
* Use markdown for documentation.

That's all

## Codemap

* At `include`, there should only be headers.
* On `include/fq`, there should be internal-er stuff.
* On `src`, there should be the actual implementation sources.
* On `test`, there should be test stuff. No framework is used in particular.
