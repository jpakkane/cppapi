/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Jussi Pakkanen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if defined __GNUC__
  #define FOO_PUBLIC __attribute__ ((visibility("default")))
#else
  #pragma message ("Compiler does not support symbol visibility.")
  #define FOO_PUBLIC
#endif

struct Foo;

FOO_PUBLIC struct Foo* foo_new();
FOO_PUBLIC struct Foo* foo_new_with_number(int i);
void FOO_PUBLIC foo_destroy(struct Foo* f);

/* error must point to nullptr and will be changed to
 * point to a string on error. Caller must free it with
 * free().
 */
FOO_PUBLIC int foo_get_zero(struct Foo* f, char **error);
FOO_PUBLIC int foo_throw_exception(struct Foo* f, char **error);

#ifdef __cplusplus
}
#endif
