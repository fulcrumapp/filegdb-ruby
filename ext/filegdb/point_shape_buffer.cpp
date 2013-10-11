
#include "point.hpp"
#include "shape_buffer.hpp"
#include "point_shape_buffer.hpp"

namespace filegdb {

VALUE point_shape_buffer::_klass = Qnil;

VALUE point_shape_buffer::klass() {
  return point_shape_buffer::_klass;
}

VALUE point_shape_buffer::setup(VALUE self, VALUE shapeType) {
  point_shape_buffer *shape = unwrap(self);

  ShapeType nshape_type = (ShapeType)FIX2INT(shapeType);

  fgdbError hr = shape->value().Setup(nshape_type);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  return shape->wrapped();
}

VALUE point_shape_buffer::get_point(VALUE self) {
  point_shape_buffer *shape = unwrap(self);

  Point *out = NULL;

  fgdbError hr = shape->value().GetPoint(out);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  point *result = new point(out);

  return result->wrapped();
}

void point_shape_buffer::define(VALUE module)
{
  point_shape_buffer::_klass = rb_define_class_under(module, "PointShapeBuffer", shape_buffer::_klass);
  base::define(point_shape_buffer::_klass, true);
  rb_define_method(point_shape_buffer::_klass, "setup", FGDB_METHOD(point_shape_buffer::setup), 1);
  rb_define_method(point_shape_buffer::_klass, "get_point", FGDB_METHOD(point_shape_buffer::get_point), 0);
}

}

