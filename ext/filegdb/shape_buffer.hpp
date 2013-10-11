#ifndef __FGDB_SHAPE_BUFFER_HPP__
#define __FGDB_SHAPE_BUFFER_HPP__

#include "filegdb.hpp"
#include "shape_buffer_base.hpp"

namespace filegdb {
  class shape_buffer : public shape_buffer_base<shape_buffer, ShapeBuffer> {
  public:
    static void define(VALUE module);

    virtual VALUE klass();

    static VALUE _klass;

    virtual ~shape_buffer() {};
  };
}

#endif
