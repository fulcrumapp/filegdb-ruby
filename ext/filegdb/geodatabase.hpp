#ifndef __FGDB_GEODATABASE_HPP__
#define __FGDB_GEODATABASE_HPP__

#include "filegdb.hpp"
#include "base.hpp"

namespace filegdb {
  class table;

  class geodatabase : public base<geodatabase> {
  public:
    geodatabase();
    static VALUE create(VALUE klass, VALUE filename);
    static VALUE open(VALUE klass, VALUE filename);
    static VALUE delete_database(VALUE klass, VALUE filename);
    static VALUE close(VALUE self);
    static VALUE create_table(VALUE self, VALUE table_name, VALUE table_definition);
    static VALUE open_table(VALUE self, VALUE table_name);
    static VALUE get_child_datasets(VALUE self, VALUE parent_path, VALUE dataset_type);
    static VALUE get_dataset_definition(VALUE self, VALUE path, VALUE dataset_type);
    static VALUE get_dataset_types(VALUE self);
    static VALUE get_dataset_relationship_types(VALUE self);

    static void define(VALUE module);

    virtual ~geodatabase();

    virtual void mark();
    virtual VALUE klass();

    static VALUE _klass;

  private:
    Geodatabase *_gdb;
    std::vector<table *> _tables;
  };
}

#endif
