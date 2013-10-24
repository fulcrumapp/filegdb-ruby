#include "ruby.h"
#include <string>
#include <iostream>

#include "filegdb.hpp"
#include "geodatabase.hpp"
#include "table.hpp"
#include "row.hpp"
#include "shape_buffer.hpp"
#include "point_shape_buffer.hpp"
#include "multi_point_shape_buffer.hpp"
#include "point.hpp"
#include "field_info.hpp"

VALUE cFileGDB;

extern "C" {
  void Init_filegdb() {
    cFileGDB = rb_define_module("FileGDB");
    filegdb::geodatabase::define(cFileGDB);
    filegdb::table::define(cFileGDB);
    filegdb::row::define(cFileGDB);
    filegdb::point::define(cFileGDB);
    filegdb::shape_buffer::define(cFileGDB);
    filegdb::point_shape_buffer::define(cFileGDB);
    filegdb::multi_point_shape_buffer::define(cFileGDB);
    filegdb::field_info::define(cFileGDB);
  }
}
