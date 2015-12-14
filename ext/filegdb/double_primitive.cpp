#include "double_primitive.hpp"

namespace filegdb {

VALUE double_primitive::_klass = Qnil;

VALUE double_primitive::klass() {
  return double_primitive::_klass;
}

VALUE double_primitive::set_value(VALUE self, VALUE value) {
  CHECK_ARGUMENT_FLOAT(value);

  double_primitive *prim = unwrap(self);

  *prim->_value = NUM2DBL(value);

  return prim->wrapped();
}

VALUE double_primitive::get_value(VALUE self) {
  double_primitive *prim = unwrap(self);
  return rb_float_new(*prim->_value);
}

void double_primitive::define(VALUE module)
{
  double_primitive::_klass = rb_define_class_under(module, "DoublePrimitive", rb_cObject);
  base::define(double_primitive::_klass, true);
  rb_define_method(double_primitive::_klass, "value", FGDB_METHOD(double_primitive::get_value), 0);
  rb_define_method(double_primitive::_klass, "value=", FGDB_METHOD(double_primitive::set_value), 1);
}

}
