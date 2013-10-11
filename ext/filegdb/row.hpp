#ifndef __FGDB_ROW_HPP__
#define __FGDB_ROW_HPP__

#include "filegdb.hpp"
#include "table.hpp"

namespace filegdb {
  class row : public base<row> {
  public:
    row() : base<row>() {};
    row(table *table);
    static void define(VALUE module);
    static VALUE set_string(VALUE self, VALUE column, VALUE value);
    static VALUE get_string(VALUE self, VALUE column);
    static VALUE set_geometry(VALUE self, VALUE geometry);
    static VALUE get_geometry(VALUE self);
    static VALUE set_date(VALUE self, VALUE column, VALUE date);
    static VALUE get_date(VALUE self, VALUE column);
    static VALUE set_double(VALUE self, VALUE column, VALUE number);
    static VALUE get_double(VALUE self, VALUE column);
    static VALUE set_integer(VALUE self, VALUE column, VALUE integer);
    static VALUE get_integer(VALUE self, VALUE column);

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

