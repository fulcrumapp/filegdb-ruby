#ifndef __FGDB_TABLE_HPP__
#define __FGDB_TABLE_HPP__

#include "fgdb.hpp"
#include "geodatabase.hpp"

namespace fgdb {
  class table : public base<table> {
  public:
    table() : base<table>() {};
    table(geodatabase *db);
    virtual VALUE initialize(int argc, VALUE *argv);
    static VALUE create_row_object(VALUE self);
    static VALUE insert(VALUE self, VALUE row);
    static void define(VALUE module);

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
