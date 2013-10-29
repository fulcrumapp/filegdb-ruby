
#include "integer_primitive.hpp"

namespace filegdb {

VALUE integer_primitive::_klass = Qnil;

VALUE integer_primitive::klass() {
  return integer_primitive::_klass;
}


VALUE integer_primitive::set_value(VALUE self, VALUE value) {
  CHECK_ARGUMENT_FIXNUM(value);

  integer_primitive *prim = unwrap(self);

  *prim->_value = FIX2INT(value);

  return prim->wrapped();
}

VALUE integer_primitive::get_value(VALUE self) {
  integer_primitive *prim = unwrap(self);
  return INT2FIX(*prim->_value);
}

void integer_primitive::define(VALUE module)
{
  integer_primitive::_klass = rb_define_class_under(module, "IntegerPrimitive", rb_cObject);
  base::define(integer_primitive::_klass, true);
  rb_define_method(integer_primitive::_klass, "value", FGDB_METHOD(integer_primitive::get_value), 0);
  rb_define_method(integer_primitive::_klass, "value=", FGDB_METHOD(integer_primitive::set_value), 1);
}

}
