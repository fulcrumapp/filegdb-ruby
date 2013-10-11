
#include "point.hpp"
#include "shape_buffer.hpp"
#include "multi_point_shape_buffer.hpp"

namespace filegdb {

VALUE multi_point_shape_buffer::_klass = Qnil;

VALUE multi_point_shape_buffer::klass() {
  return multi_point_shape_buffer::_klass;
}

VALUE multi_point_shape_buffer::setup(VALUE self, VALUE shapeType, VALUE numberOfPoints) {
  CHECK_ARGUMENT_FIXNUM(shapeType);
  CHECK_ARGUMENT_FIXNUM(numberOfPoints);

  multi_point_shape_buffer *shape = unwrap(self);

  ShapeType nshape_type = (ShapeType)FIX2INT(shapeType);

  fgdbError hr = shape->value().Setup(nshape_type, FIX2INT(numberOfPoints));

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  return shape->wrapped();
}

VALUE multi_point_shape_buffer::get_points(VALUE self) {
  multi_point_shape_buffer *shape = unwrap(self);

  Point *points = NULL;

  fgdbError hr = shape->value().GetPoints(points);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  int numPoints = 0;

  hr = shape->value().GetNumPoints(numPoints);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  VALUE arrayOfPoints = rb_ary_new();

  for (int i = 0; i < numPoints; ++i) {
    point *p = new point(&points[i]);
    rb_ary_push(arrayOfPoints, p->wrapped());
  }

  return arrayOfPoints;
}

VALUE multi_point_shape_buffer::get_num_points(VALUE self) {
  multi_point_shape_buffer *shape = unwrap(self);

  int numPoints = 0;

  fgdbError hr = shape->value().GetNumPoints(numPoints);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  return INT2FIX(numPoints);
}

void multi_point_shape_buffer::define(VALUE module)
{
  multi_point_shape_buffer::_klass = rb_define_class_under(module, "MultiPointShapeBuffer", shape_buffer::_klass);
  base::define(multi_point_shape_buffer::_klass, true);
  rb_define_method(multi_point_shape_buffer::_klass, "setup", FGDB_METHOD(multi_point_shape_buffer::setup), 2);
  rb_define_method(multi_point_shape_buffer::_klass, "get_points", FGDB_METHOD(multi_point_shape_buffer::get_points), 0);
  rb_define_method(multi_point_shape_buffer::_klass, "get_num_points", FGDB_METHOD(multi_point_shape_buffer::get_num_points), 0);
}

}


