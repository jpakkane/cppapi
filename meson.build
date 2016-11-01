project('c/c++ api example', 'c', 'cpp',
  default_options : ['cpp_std=c++14'])

flib = shared_library('foo', 'fooimpl.cpp',
  cpp_args : '-fvisibility=hidden',
  link_args : '-fvisibility=hidden',
)
