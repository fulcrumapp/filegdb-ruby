#include "point.hpp"
#include "shape_buffer.hpp"
#include "multi_part_shape_buffer.hpp"
#include "integer_primitive.hpp"
#include "double_primitive.hpp"

namespace filegdb {

VALUE multi_part_shape_buffer::_klass = Qnil;

VALUE multi_part_shape_buffer::klass() {
  return multi_part_shape_buffer::_klass;
}

VALUE multi_part_shape_buffer::setup(VALUE self, VALUE shapeType, VALUE numberOfParts, VALUE numberOfPoints) {
  CHECK_ARGUMENT_FIXNUM(shapeType);
  CHECK_ARGUMENT_FIXNUM(numberOfParts);
  CHECK_ARGUMENT_FIXNUM(numberOfPoints);

  multi_part_shape_buffer *shape = unwrap(self);

  ShapeType nshape_type = (ShapeType)FIX2INT(shapeType);

  fgdbError hr = shape->value().Setup(nshape_type, FIX2INT(numberOfParts), FIX2INT(numberOfPoints));

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  return shape->wrapped();
}

VALUE multi_part_shape_buffer::get_points(VALUE self) {
  multi_part_shape_buffer *shape = unwrap(self);

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

VALUE multi_part_shape_buffer::get_parts(VALUE self) {
  multi_part_shape_buffer *shape = unwrap(self);

  int *parts = NULL;

  fgdbError hr = shape->value().GetParts(parts);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  int numParts = 0;

  hr = shape->value().GetNumParts(numParts);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  VALUE arrayOfParts = rb_ary_new();

  for (int i = 0; i < numParts; ++i) {
    integer_primitive *value = new integer_primitive(&parts[i]);
    rb_ary_push(arrayOfParts, value->wrapped());
  }

  return arrayOfParts;
}

VALUE multi_part_shape_buffer::get_num_points(VALUE self) {
  multi_part_shape_buffer *shape = unwrap(self);

  int numPoints = 0;

  fgdbError hr = shape->value().GetNumPoints(numPoints);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  return INT2FIX(numPoints);
}

VALUE multi_part_shape_buffer::get_num_parts(VALUE self) {
  multi_part_shape_buffer *shape = unwrap(self);

  int numParts = 0;

  fgdbError hr = shape->value().GetNumParts(numParts);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  return INT2FIX(numParts);
}

VALUE multi_part_shape_buffer::get_zs(VALUE self)
{
  multi_part_shape_buffer *shape = unwrap(self);

  double *zValues;

  fgdbError hr = shape->value().GetZs(zValues);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  int numPoints = 0;

  hr = shape->value().GetNumPoints(numPoints);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  VALUE result = rb_ary_new();

  for (int i = 0; i < numPoints; ++i) {
    rb_ary_push(result, rb_float_new(zValues[i]));
  }

  return result;
}

VALUE multi_part_shape_buffer::get_ms(VALUE self)
{
  multi_part_shape_buffer *shape = unwrap(self);

  double *mValues;

  fgdbError hr = shape->value().GetMs(mValues);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  int numPoints = 0;

  hr = shape->value().GetNumPoints(numPoints);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  VALUE result = rb_ary_new();

  for (int i = 0; i < numPoints; ++i) {
    rb_ary_push(result, rb_float_new(mValues[i]));
  }

  return result;
}

VALUE multi_part_shape_buffer::get_ids(VALUE self)
{
  multi_part_shape_buffer *shape = unwrap(self);

  int *idValues;

  fgdbError hr = shape->value().GetIDs(idValues);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  int numPoints = 0;

  hr = shape->value().GetNumPoints(numPoints);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  VALUE result = rb_ary_new();

  for (int i = 0; i < numPoints; ++i) {
    rb_ary_push(result, INT2FIX(idValues[i]));
  }

  return result;
}

VALUE multi_part_shape_buffer::get_extent(VALUE self)
{
  multi_part_shape_buffer *shape = unwrap(self);

  double *extents = NULL;

  fgdbError hr = shape->value().GetExtent(extents);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  VALUE result = rb_ary_new();

  rb_ary_push(result, DBL2NUM(extents[0]));
  rb_ary_push(result, DBL2NUM(extents[1]));
  rb_ary_push(result, DBL2NUM(extents[2]));
  rb_ary_push(result, DBL2NUM(extents[3]));

  return result;
}

VALUE multi_part_shape_buffer::get_z_extent(VALUE self)
{
  multi_part_shape_buffer *shape = unwrap(self);

  double *extents = NULL;

  fgdbError hr = shape->value().GetZExtent(extents);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  VALUE result = rb_ary_new();

  rb_ary_push(result, DBL2NUM(extents[0]));
  rb_ary_push(result, DBL2NUM(extents[1]));

  return result;
}

VALUE multi_part_shape_buffer::get_m_extent(VALUE self)
{
  multi_part_shape_buffer *shape = unwrap(self);

  double *extents = NULL;

  fgdbError hr = shape->value().GetMExtent(extents);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  VALUE result = rb_ary_new();

  rb_ary_push(result, DBL2NUM(extents[0]));
  rb_ary_push(result, DBL2NUM(extents[1]));

  return result;
}

VALUE multi_part_shape_buffer::calculate_extent(VALUE self)
{
  multi_part_shape_buffer *shape = unwrap(self);

  fgdbError hr = shape->value().CalculateExtent();

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
  }

  return Qnil;
}

void multi_part_shape_buffer::define(VALUE module)
{
  multi_part_shape_buffer::_klass = rb_define_class_under(module, "MultiPartShapeBuffer", shape_buffer::_klass);
  base::define(multi_part_shape_buffer::_klass, true);
  rb_define_method(multi_part_shape_buffer::_klass, "setup", FGDB_METHOD(multi_part_shape_buffer::setup), 3);
  rb_define_method(multi_part_shape_buffer::_klass, "get_points", FGDB_METHOD(multi_part_shape_buffer::get_points), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "get_parts", FGDB_METHOD(multi_part_shape_buffer::get_parts), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "get_num_points", FGDB_METHOD(multi_part_shape_buffer::get_num_points), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "get_num_parts", FGDB_METHOD(multi_part_shape_buffer::get_num_parts), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "z", FGDB_METHOD(multi_part_shape_buffer::get_zs), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "m", FGDB_METHOD(multi_part_shape_buffer::get_ms), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "id", FGDB_METHOD(multi_part_shape_buffer::get_ids), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "get_extent", FGDB_METHOD(multi_part_shape_buffer::get_extent), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "get_z_extent", FGDB_METHOD(multi_part_shape_buffer::get_z_extent), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "get_m_extent", FGDB_METHOD(multi_part_shape_buffer::get_m_extent), 0);
  rb_define_method(multi_part_shape_buffer::_klass, "calculate_extent", FGDB_METHOD(multi_part_shape_buffer::calculate_extent), 0);
}

}



