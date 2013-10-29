#ifndef __FGDB_INTEGER_PRIMITIVE_HPP__
#define __FGDB_INTEGER_PRIMITIVE_HPP__

#include "filegdb.hpp"
#include "base.hpp"
#include "primitive.hpp"

namespace filegdb {

class integer_primitive : public primitive<int, integer_primitive> {
public:
  integer_primitive() {}

  integer_primitive(int *value) : primitive(value) {}

  virtual VALUE klass();

  static VALUE _klass;

  static void define(VALUE module);

  static VALUE set_value(VALUE self, VALUE value);

  static VALUE get_value(VALUE self);
};

}

#endif
