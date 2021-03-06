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
#define FGDB_RAISE_ERROR(hr) rb_raise(rb_eRuntimeError, "%s", fgdb_error_string(hr).c_str())
#define FGDB_FATAL(msg) rb_raise(rb_eRuntimeError, "%s", msg)
#define FGDB_FATAL_ARGUMENT(msg) rb_raise(rb_eArgError, "%s", msg)
#define FGDB_METHOD(method) ((RB_INSTANCE_METHOD)&method)

#define CHECK_ARGUMENT_STRING(arg) \
  if (TYPE(arg) != T_STRING) { \
    FGDB_FATAL_ARGUMENT("Argument must be a String"); \
    return Qnil; \
  }

#define CHECK_ARGUMENT_FIXNUM(arg) \
  if (TYPE(arg) != T_FIXNUM) { \
    FGDB_FATAL_ARGUMENT("Argument must be a FixNum"); \
    return Qnil; \
  }

#define CHECK_ARGUMENT_FLOAT(arg) \
  if (TYPE(arg) != T_FLOAT) { \
    FGDB_FATAL_ARGUMENT("Argument must be a Float"); \
    return Qnil; \
  }

const std::wstring to_wstring(const char *input);
const std::string to_string(std::wstring str);
const std::string fgdb_error_string(fgdbError hr);

extern VALUE fgdb_klass;

#endif
