#ifndef __FGDB_MULTI_POINT_SHAPE_BUFFER_HPP__
#define __FGDB_MULTI_POINT_SHAPE_BUFFER_HPP__

#include "filegdb.hpp"
#include "shape_buffer_base.hpp"

namespace filegdb {
  class multi_point_shape_buffer : public shape_buffer_base<multi_point_shape_buffer, MultiPointShapeBuffer> {
  public:
    static void define(VALUE module);

    static VALUE setup(VALUE self, VALUE shapeType, VALUE numberOfPoints);
    static VALUE extents(VALUE self);
    /* static VALUE get_point(VALUE self); */
    /* static VALUE get_z(VALUE self); */
    /* static VALUE get_m(VALUE self); */
    /* static VALUE get_id(VALUE self); */
    /* static VALUE set_z(VALUE self, VALUE zValue); */
    /* static VALUE set_m(VALUE self, VALUE mValue); */
    /* static VALUE set_id(VALUE self, VALUE idValue); */

    virtual VALUE klass();

    static VALUE _klass;

    virtual ~multi_point_shape_buffer() {};
  };
}

#endif




