#ifndef __FGDB_MULTI_PART_SHAPE_BUFFER_HPP__
#define __FGDB_MULTI_PART_SHAPE_BUFFER_HPP__

#include "filegdb.hpp"
#include "shape_buffer_base.hpp"

namespace filegdb {
  class multi_part_shape_buffer : public shape_buffer_base<multi_part_shape_buffer, MultiPartShapeBuffer> {
  public:
    static void define(VALUE module);

    static VALUE setup(VALUE self, VALUE shapeType, VALUE numberOfParts, VALUE numberOfPoints);
    static VALUE get_points(VALUE self);
    static VALUE get_num_points(VALUE self);
    static VALUE get_num_parts(VALUE self);
    static VALUE get_zs(VALUE self);
    static VALUE get_ms(VALUE self);
    static VALUE get_ids(VALUE self);
    static VALUE get_extent(VALUE self);
    static VALUE get_z_extent(VALUE self);
    static VALUE get_m_extent(VALUE self);
    static VALUE calculate_extent(VALUE self);

    virtual VALUE klass();

    static VALUE _klass;

    virtual ~multi_part_shape_buffer() {};
  };
}

#endif





