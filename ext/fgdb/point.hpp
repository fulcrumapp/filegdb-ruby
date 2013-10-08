#ifndef __FGDB_POINT_HPP__
#define __FGDB_POINT_HPP__

#include "fgdb.hpp"
#include "base.hpp"

namespace fgdb {
  class point : public base<point> {
  public:
    point() : value(0) {};
    point(Point *p) : value(p) {};
    static void define(VALUE module);

    static VALUE set_x(VALUE self, VALUE x);
    static VALUE get_x(VALUE self);

    static VALUE set_y(VALUE self, VALUE y);
    static VALUE get_y(VALUE self);

    virtual VALUE klass();

    static VALUE _klass;

    virtual ~point() {};

    virtual VALUE initialize(int argc, VALUE *argv) { return initialize_not_allowed(); }

    Point *value;
  };
}

#endif

