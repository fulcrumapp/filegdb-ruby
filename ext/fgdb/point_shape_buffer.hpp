#ifndef __FGDB_POINT_SHAPE_BUFFER_HPP__
#define __FGDB_POINT_SHAPE_BUFFER_HPP__

#include "fgdb.hpp"
#include "shape_buffer_base.hpp"

namespace fgdb {
  class point_shape_buffer : public shape_buffer_base<point_shape_buffer, PointShapeBuffer> {
  public:
    static void define(VALUE module);

    static VALUE setup(VALUE self, VALUE shapeType);
    static VALUE get_point(VALUE self);

    virtual VALUE klass();

    static VALUE _klass;

    virtual ~point_shape_buffer() {};
  };
}

#endif



