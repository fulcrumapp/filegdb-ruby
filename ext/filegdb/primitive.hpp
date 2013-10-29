#ifndef __FGDB_PRIMITIVE_HPP__
#define __FGDB_PRIMITIVE_HPP__

#include "filegdb.hpp"

namespace filegdb {
  template<typename T, typename K> class primitive : public base<K> {
  public:
    primitive() : _value(new T) {}
    primitive(T value) : _value(new T(value)) {}

    virtual ~primitive() {
      if (_value) {
        delete _value;
        _value = NULL;
      }
    }

  protected:
    T *_value;
  };

  class integer_primitive : public primitive<int, integer_primitive> {
  public:
    virtual VALUE klass() {
      return integer_primitive::_klass;
    }

    static VALUE _klass;

    static void define(VALUE module) {
      integer_primitive::_klass = rb_define_class_under(module, "IntegerPrimitive", rb_cObject);
      base::define(integer_primitive::_klass, true);
      rb_define_method(integer_primitive::_klass, "value", FGDB_METHOD(integer_primitive::get_value), 0);
      rb_define_method(integer_primitive::_klass, "value=", FGDB_METHOD(integer_primitive::set_value), 1);
    }

    static VALUE set_value(VALUE self, VALUE value) {
      CHECK_ARGUMENT_FIXNUM(value);

      integer_primitive *prim = unwrap(self);

      *prim->_value = FIX2INT(value);

      return prim->wrapped();
    }

    static VALUE get_value(VALUE self) {
      integer_primitive *prim = unwrap(self);
      return INT2FIX(*prim->_value);
    }
  };

  VALUE integer_primitive::_klass = Qnil;



  class double_primitive : public primitive<double, double_primitive> {
  public:
    virtual VALUE klass() {
      return double_primitive::_klass;
    }

    static VALUE _klass;

    static void define(VALUE module) {
      double_primitive::_klass = rb_define_class_under(module, "DoublePrimitive", rb_cObject);
      base::define(double_primitive::_klass, true);
      rb_define_method(double_primitive::_klass, "value", FGDB_METHOD(double_primitive::get_value), 0);
      rb_define_method(double_primitive::_klass, "value=", FGDB_METHOD(double_primitive::set_value), 1);
    }

    static VALUE set_value(VALUE self, VALUE value) {
      CHECK_ARGUMENT_FLOAT(value);

      double_primitive *prim = unwrap(self);

      *prim->_value = NUM2DBL(value);

      return prim->wrapped();
    }

    static VALUE get_value(VALUE self) {
      double_primitive *prim = unwrap(self);
      return rb_float_new(*prim->_value);
    }
  };

  VALUE double_primitive::_klass = Qnil;
}



#endif






