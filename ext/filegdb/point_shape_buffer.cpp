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

VALUE point_shape_buffer::get_z(VALUE self) {
  point_shape_buffer *shape = unwrap(self);

  double *result = NULL;

  fgdbError hr = shape->value().GetZ(result);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_float_new(*result);
}

VALUE point_shape_buffer::get_m(VALUE self) {
  point_shape_buffer *shape = unwrap(self);

  double *result = NULL;

  fgdbError hr = shape->value().GetM(result);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_float_new(*result);
}

VALUE point_shape_buffer::get_id(VALUE self) {
  point_shape_buffer *shape = unwrap(self);

  int *result = NULL;

  fgdbError hr = shape->value().GetID(result);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return INT2FIX(*result);
}

VALUE point_shape_buffer::set_z(VALUE self, VALUE zValue) {
  CHECK_ARGUMENT_FLOAT(zValue);

  point_shape_buffer *shape = unwrap(self);

  double *result = NULL;

  fgdbError hr = shape->value().GetZ(result);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  *result = NUM2DBL(zValue);

  return zValue;
}

VALUE point_shape_buffer::set_m(VALUE self, VALUE mValue) {
  CHECK_ARGUMENT_FLOAT(mValue);

  point_shape_buffer *shape = unwrap(self);

  double *result = NULL;

  fgdbError hr = shape->value().GetM(result);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  *result = NUM2DBL(mValue);

  return mValue;
}

VALUE point_shape_buffer::set_id(VALUE self, VALUE idValue) {
  CHECK_ARGUMENT_FIXNUM(idValue);

  point_shape_buffer *shape = unwrap(self);

  int *result = NULL;

  fgdbError hr = shape->value().GetID(result);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  *result = FIX2INT(idValue);

  return idValue;
}

void point_shape_buffer::define(VALUE module)
{
  point_shape_buffer::_klass = rb_define_class_under(module, "PointShapeBuffer", shape_buffer::_klass);
  base::define(point_shape_buffer::_klass, true);
  rb_define_method(point_shape_buffer::_klass, "setup", FGDB_METHOD(point_shape_buffer::setup), 1);
  rb_define_method(point_shape_buffer::_klass, "get_point", FGDB_METHOD(point_shape_buffer::get_point), 0);
  rb_define_method(point_shape_buffer::_klass, "z", FGDB_METHOD(point_shape_buffer::get_z), 0);
  rb_define_method(point_shape_buffer::_klass, "m", FGDB_METHOD(point_shape_buffer::get_m), 0);
  rb_define_method(point_shape_buffer::_klass, "id", FGDB_METHOD(point_shape_buffer::get_id), 0);
  rb_define_method(point_shape_buffer::_klass, "z=", FGDB_METHOD(point_shape_buffer::set_z), 1);
  rb_define_method(point_shape_buffer::_klass, "m=", FGDB_METHOD(point_shape_buffer::set_m), 1);
  rb_define_method(point_shape_buffer::_klass, "id=", FGDB_METHOD(point_shape_buffer::set_id), 1);
}

}

