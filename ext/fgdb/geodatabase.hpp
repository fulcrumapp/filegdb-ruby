#ifndef __FGDB_GEODATABASE_HPP__
#define __FGDB_GEODATABASE_HPP__

#include "fgdb.hpp"
#include "base.hpp"

namespace fgdb {
  class table;

  class geodatabase : public base<geodatabase> {
  public:
    geodatabase();
    static VALUE create(VALUE klass, VALUE filename);
    static VALUE open(VALUE klass, VALUE filename);
    static VALUE create_table(VALUE self, VALUE table_name, VALUE table_definition);
    static VALUE get_child_datasets(VALUE self, VALUE parent_path, VALUE dataset_type);
    static VALUE get_dataset_definition(VALUE self, VALUE path, VALUE dataset_type);

    static void define(VALUE module);

    virtual ~geodatabase();

    virtual VALUE initialize(int argc, VALUE *argv);
    virtual void mark();
    virtual VALUE klass();

    static VALUE _klass;

  private:
    Geodatabase *_gdb;
    std::vector<table *> _tables;
  };
}

#endif
