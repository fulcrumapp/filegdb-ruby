#include "point.hpp"

namespace filegdb {

VALUE point::_klass = Qnil;

VALUE point::klass() {
  return point::_klass;
}

VALUE point::set_x(VALUE self, VALUE x) {
  unwrap(self)->value->x = NUM2DBL(x);

  return x;
}

VALUE point::get_x(VALUE self) {
  return rb_float_new(unwrap(self)->value->x);
}

VALUE point::set_y(VALUE self, VALUE y) {
  unwrap(self)->value->y = NUM2DBL(y);

  return y;
}

VALUE point::get_y(VALUE self) {
  return rb_float_new(unwrap(self)->value->y);
}

void point::define(VALUE module)
{
  point::_klass = rb_define_class_under(module, "Point", rb_cObject);
  base::define(point::_klass, false);
  rb_define_method(point::_klass, "x=", FGDB_METHOD(point::set_x), 1);
  rb_define_method(point::_klass, "x", FGDB_METHOD(point::get_x), 0);
  rb_define_method(point::_klass, "y=", FGDB_METHOD(point::set_y), 1);
  rb_define_method(point::_klass, "y", FGDB_METHOD(point::get_y), 0);
}

}


