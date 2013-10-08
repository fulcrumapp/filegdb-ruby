#include "ruby.h"
#include <string>
#include <iostream>

#include "fgdb.hpp"
#include "geodatabase.hpp"
#include "table.hpp"
#include "row.hpp"
#include "shape_buffer.hpp"
#include "point_shape_buffer.hpp"
#include "point.hpp"

VALUE cFGDB;

extern "C" {
  void Init_fgdb() {
    cFGDB = rb_define_module("FGDB");
    fgdb::geodatabase::define(cFGDB);
    fgdb::table::define(cFGDB);
    fgdb::row::define(cFGDB);
    fgdb::point::define(cFGDB);
    fgdb::shape_buffer::define(cFGDB);
    fgdb::point_shape_buffer::define(cFGDB);
    fgdb::point_shape_buffer::define(cFGDB);
  }
}
