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

    virtual VALUE klass();
    static VALUE _klass;

    FieldInfo &value() { return *_fieldInfo; }

    virtual ~field_info();

  private:
    FieldInfo *_fieldInfo;
  };
}

#endif

