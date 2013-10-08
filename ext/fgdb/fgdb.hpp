#ifndef __FGDB_HPP__
#define __FGDB_HPP__

#include "ruby.h"
#include <string>
#include <iostream>
#include <FileGDBAPI.h>

using namespace std;
using namespace FileGDBAPI;

typedef VALUE (*RB_INSTANCE_METHOD)(...);

#define FGDB_IS_FAILURE(hr) ((hr) != S_OK)
#define FGDB_RAISE_ERROR(hr) rb_raise(rb_eRuntimeError, fgdb_error_string(hr))
#define FGDB_FATAL(msg) rb_raise(rb_eRuntimeError, msg)
#define FGDB_METHOD(method) ((RB_INSTANCE_METHOD)&method)

std::wstring to_wstring(const char *input);
const char *to_char_array(std::wstring str);
const char *fgdb_error_string(fgdbError hr);


extern VALUE fgdb_klass;

#endif
