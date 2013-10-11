#ifndef __FGDB_MULTI_POINT_SHAPE_BUFFER_HPP__
#define __FGDB_MULTI_POINT_SHAPE_BUFFER_HPP__

#include "filegdb.hpp"
#include "shape_buffer_base.hpp"

namespace filegdb {
  class multi_point_shape_buffer : public shape_buffer_base<multi_point_shape_buffer, MultiPointShapeBuffer> {
  public:
    static void define(VALUE module);

    static VALUE setup(VALUE self, VALUE shapeType, VALUE numberOfPoints);
    static VALUE get_points(VALUE self);

    virtual VALUE klass();

    static VALUE _klass;

    virtual ~multi_point_shape_buffer() {};
  };
}

#endif




