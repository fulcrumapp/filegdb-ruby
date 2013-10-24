#ifndef __FGDB_TABLE_HPP__
#define __FGDB_TABLE_HPP__

#include "filegdb.hpp"
#include "geodatabase.hpp"

namespace filegdb {
  class table : public base<table> {
  public:
    table() : base<table>(), _table(0) {};
    table(geodatabase *db);
    static VALUE create_row_object(VALUE self);
    static VALUE insert(VALUE self, VALUE row);
    static void define(VALUE module);

    static VALUE get_definition(VALUE self);
    static VALUE get_documentation(VALUE self);

    virtual VALUE klass();
    static VALUE _klass;

    Table &value() { return *_table; }

    virtual ~table();

  private:
    Table *_table;
    geodatabase *_db;
  };
}

#endif
