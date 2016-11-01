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

#include"foo-internal.h"
#include"foo.h" // for simplicity
#include<stdexcept>
#include<cstring>
#include<cstdlib>
#include<cassert>

FooInternal::FooInternal() {
}

FooInternal::FooInternal(int)  {
    throw std::runtime_error("Wrong construction.");
}


int FooInternal::get_zero() const {
    return 0;
}

int FooInternal::throw_exception() {
    throw std::logic_error("Wrong call.");
}

// C API portion here.

void convert_exception(char **error) noexcept {
    char *msg;
    assert(!*error);
    try {
        throw;
    } catch(const std::exception &e) {
      msg = strdup(e.what());
    } catch(...) {
        msg = strdup("An unknown error happened.");
    }
    *error = msg;
}

extern "C" {

struct Foo* foo_new() {
    try {
        return reinterpret_cast<Foo*>(new FooInternal());
    } catch(...) {
        return nullptr; // Function does not take an error argument so just return null.
    }
}

struct Foo* foo_new_with_number(int i) {
    try {
        return reinterpret_cast<Foo*>(new FooInternal(i));
    } catch(...) {
        return nullptr;
    }
}

void foo_destroy(struct Foo* f) {
    delete reinterpret_cast<FooInternal*>(f);
}

int foo_get_zero(struct Foo* f, char **error) {
    try {
        return reinterpret_cast<FooInternal*>(f)->get_zero();
    } catch(...) {
        convert_exception(error);
        return -1;
    }
}

int foo_throw_exception(struct Foo* f, char **error) {
    try {
        return reinterpret_cast<FooInternal*>(f)->throw_exception();
    } catch(...) {
        convert_exception(error);
        return -1;
    }
}

}
