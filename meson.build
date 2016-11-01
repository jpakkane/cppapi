project('c/c++ api example', 'c', 'cpp',
  default_options : ['cpp_std=c++14',
                  'warning_level=3'])

# This library exports a plain C API.
flib = shared_library('foo', 'fooimpl.cpp',
  cpp_args : '-fvisibility=hidden',
  link_args : '-fvisibility=hidden',
)

cprog = executable('cprog', 'cprog.c',
  link_with : flib)

test('cprog', cprog)

cppprog = executable('cppprog', 'cppprog.cpp',
  link_with : flib)

test('cppprog', cppprog)
