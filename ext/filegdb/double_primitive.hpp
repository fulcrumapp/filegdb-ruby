#ifndef __FGDB_DOUBLE_PRIMITIVE_HPP__
#define __FGDB_DOUBLE_PRIMITIVE_HPP__

#include "filegdb.hpp"
#include "base.hpp"
#include "primitive.hpp"

namespace filegdb {

class double_primitive : public primitive<double, double_primitive> {
public:
  double_primitive() {}

  double_primitive(double *value) : primitive(value) {}

  virtual VALUE klass();

  static VALUE _klass;

  static void define(VALUE module);

  static VALUE set_value(VALUE self, VALUE value);

  static VALUE get_value(VALUE self);
};

}

#endif
