#ifndef __FGDB_POINT_SHAPE_BUFFER_HPP__
#define __FGDB_POINT_SHAPE_BUFFER_HPP__

#include "filegdb.hpp"
#include "shape_buffer_base.hpp"

namespace filegdb {
  class point_shape_buffer : public shape_buffer_base<point_shape_buffer, PointShapeBuffer> {
  public:
    static void define(VALUE module);

    static VALUE setup(VALUE self, VALUE shapeType);
    static VALUE get_point(VALUE self);
    static VALUE get_z(VALUE self);
    static VALUE get_m(VALUE self);
    static VALUE get_id(VALUE self);
    static VALUE set_z(VALUE self, VALUE zValue);
    static VALUE set_m(VALUE self, VALUE mValue);
    static VALUE set_id(VALUE self, VALUE idValue);

    virtual VALUE klass();

    static VALUE _klass;

    virtual ~point_shape_buffer() {};
  };
}

#endif



