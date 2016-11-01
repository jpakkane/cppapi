# Exposing a C++ library with a plain C API

One of the big complaints of `C++` is that it has an unstable API.
Since almost all runtimes expect a plain C calling conventions,
C++ libraries can not be used.

Since C++ supports C natively, providing a plain C api is actually
quite straightforward, requiring only a small amount of boilerplate. The
basic technique is presented in the CppCon 2014 presentation on [hourglass
shaped interfaces](https://www.youtube.com/watch?v=PVYdHDm0q6Y).

Most parts are straightforward. A method `Foo::func(int)` becomes
`foo_func(struct CFoo*, int, char **error)` in the C api. Here we
report errors in the way [GLib](https://www.gtk.org) does it,
with an extra error parameter.

The only tricky part is this error value. Converting between exceptions
and error codes in every function call is tedious. This can be made a lot
simpler with [Lippincott function](https://cppsecrets.blogspot.fi/2013/12/using-lippincott-function-for.html).
Its implementation can be found in `fooimpl.cpp:convert_exception`.

# Extra bonus round

The file `foo.hh` contains a C++ convenience wrapper that converts plain C
error codes back into exceptions. Thus any C++ library user can just include
that and they get a C++ API that behaves just like a regular C++ API including
passing exceptions through the shared library boundary layer while maintaining
100% plain C ABI stability.

This implementation only passes a string as the error. A fancier program could
have an error struct or the like.

# Performance overhead

There is only a slight performance overhead. Every call over the shared library
boundary becomes two function calls, one over the boundary in C and the other
as a C++ method call inside the library. However intra-library calls happen
a lot less often than inter-library calls so this is not usually an issue.

The C++ wrapper on top of C has zero overhead both in time and space.
