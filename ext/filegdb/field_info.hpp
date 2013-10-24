#ifndef __FGDB_FIELD_INFO_HPP__
#define __FGDB_FIELD_INFO_HPP__

#include "filegdb.hpp"
#include "base.hpp"

namespace filegdb {
  class field_info : public base<field_info> {
  public:
    field_info() : base<field_info>(), _fieldInfo(new FieldInfo) {};
    static void define(VALUE module);

    static VALUE get_field_count(VALUE self);
    static VALUE get_field_name(VALUE self, VALUE fieldIndex);
    static VALUE get_field_type(VALUE self, VALUE fieldIndex);
    static VALUE get_field_length(VALUE self, VALUE fieldIndex);
    static VALUE get_field_is_nullable(VALUE self, VALUE fieldIndex);

    virtual VALUE klass();
    static VALUE _klass;

    FieldInfo &value() { return *_fieldInfo; }

    virtual ~field_info();

  private:
    FieldInfo *_fieldInfo;
  };
}

#endif

