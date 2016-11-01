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

#include"foo.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv) {
    struct Foo *f;
    struct Foo *fno;
    char *error = NULL;
    int value;
    f = foo_new();
    if(!f) {
        printf("Could not create Foo object.\n");
        return 1;
    }
    fno = foo_new_with_number(42);
    if(fno) {
        printf("Created Foo even though it should not have.\n");
        return 1;
    }
    value = foo_get_zero(f, &error);
    if(error) {
        printf("Unexpected error: %s\n", error);
        free(error);
        foo_destroy(f);
        return 1;
    }
    value = foo_throw_exception(f, &error);
    if(!error) {
        printf("Error not raised even though it should have been.\n");
        foo_destroy(f);
        return 1;
    }
    free(error);
    foo_destroy(f);
    return 0;
}
