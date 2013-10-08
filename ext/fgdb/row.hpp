#ifndef __FGDB_ROW_HPP__
#define __FGDB_ROW_HPP__

#include "fgdb.hpp"
#include "table.hpp"

namespace fgdb {
  class row : public base<row> {
  public:
    row() : base<row>() {};
    row(table *table);
    virtual VALUE initialize(int argc, VALUE *argv);
    static void define(VALUE module);
    static VALUE set_string(VALUE self, VALUE column, VALUE value);
    static VALUE get_string(VALUE self, VALUE column);
    static VALUE set_geometry(VALUE self, VALUE geometry);
    static VALUE get_geometry(VALUE self);

    virtual VALUE klass();
    static VALUE _klass;

    Row &value() { return *_row; }

    virtual ~row();
  private:
    Row *_row;
    table *_table;
  };
}

#endif

