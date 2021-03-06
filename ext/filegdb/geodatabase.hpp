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
    static VALUE create_table(VALUE self, VALUE tableName, VALUE tableDefinition);
    static VALUE create_feature_dataset(VALUE self, VALUE featureSetDefinition);
    static VALUE open_table(VALUE self, VALUE tableName);
    static VALUE close_table(VALUE self, VALUE table);
    static VALUE delete_dataset(VALUE self, VALUE path, VALUE datasetType);
    static VALUE rename(VALUE self, VALUE path, VALUE datasetType, VALUE newName);
    static VALUE move(VALUE self, VALUE path, VALUE newParentPath);
    static VALUE get_child_datasets(VALUE self, VALUE parentPath, VALUE datasetType);
    static VALUE get_dataset_definition(VALUE self, VALUE path, VALUE datasetType);
    static VALUE get_dataset_documentation(VALUE self, VALUE path, VALUE datasetType);
    static VALUE get_child_dataset_definitions(VALUE self, VALUE parentPath, VALUE datasetType);
    static VALUE get_related_dataset_definitions(VALUE self, VALUE path, VALUE relType, VALUE datasetType);
    static VALUE get_dataset_types(VALUE self);
    static VALUE get_dataset_relationship_types(VALUE self);
    static VALUE get_related_datasets(VALUE self, VALUE path, VALUE relType, VALUE datasetType);
    static VALUE create_domain(VALUE self, VALUE domainDefinition);
    static VALUE alter_domain(VALUE self, VALUE domainDefinition);
    static VALUE delete_domain(VALUE self, VALUE domainName);
    static VALUE get_domain_definition(VALUE self, VALUE domainName);
    static VALUE get_query_name(VALUE self, VALUE path);

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
