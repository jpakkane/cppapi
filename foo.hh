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

#include"foo.h"
#include<memory>
#include<stdexcept>
#include<string>
#include<cstdlib>

struct FooDeleter {
    void operator()(struct Foo *f) {
        foo_destroy(f);
    }
};

// Called FooPublic only to give it a unique name.
class FooPublic {
private:
    std::unique_ptr<struct Foo, FooDeleter> p;
public:

    FooPublic() : p(foo_new()) {
        if(!p) {
            throw std::runtime_error("Could not create Foo.");
        }
    }

    FooPublic(int i) : p(foo_new_with_number(i)) {
        if(!p) {
            throw std::runtime_error("Could not create Foo.");
        }
    }

    int get_zero() {
        char *error = nullptr;
        int result = foo_get_zero(p.get(), &error);
        if(error) {
            std::string emesg(error);
            free(error);
            throw std::runtime_error(emesg); // Could be FooException.
        }
        return result;
    }

    int throw_exception() {
        char *error = nullptr;
        int result;
        result = foo_throw_exception(p.get(), &error);
        if(error) {
            std::string emesg(error);
            free(error);
            throw std::runtime_error(emesg); // Could be FooException.
        }
        return result;
    }
};
