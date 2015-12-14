#include "shape_buffer.hpp"

namespace filegdb {

VALUE shape_buffer::_klass = Qnil;

VALUE shape_buffer::klass() {
  return shape_buffer::_klass;
}

void shape_buffer::define(VALUE module)
{
  shape_buffer::_klass = rb_define_class_under(module, "ShapeBuffer", rb_cObject);
  base::define(shape_buffer::_klass, true);
}

}

