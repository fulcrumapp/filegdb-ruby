#ifndef __FILEGDB_BASE_HPP__
#define __FILEGDB_BASE_HPP__

#include <vector>
#include <algorithm>
#include "filegdb.hpp"

namespace filegdb {
  class gc_object {
  public:
    virtual void mark_dependencies() = 0;
    virtual void dispose() = 0;
    virtual void add_dependency(gc_object *dep) = 0;
    virtual void remove_dependency(gc_object *dep) = 0;
    virtual void mark() = 0;
  };

  template <typename T> class base : public gc_object {
  public:
    base<T>() : _value(0), _dependencies() {}

    static VALUE initialize_instance(int argc, VALUE *argv, VALUE self) {
      return unwrap(self)->initialize(argc, argv);
    }

    static VALUE new_instance(int argc, VALUE *argv, VALUE klass) {
      T *instance = new T();
      VALUE rvalue = instance->wrapped();
      rb_obj_call_init(rvalue, argc, argv);
      return rvalue;
    }

    static VALUE new_instance_not_allowed(int argc, VALUE *argv, VALUE klass) {
      rb_raise(rb_eRuntimeError, "You cannot use #new on this class.");
      return Qnil;
    }

    static VALUE initialize_instance_not_allowed(int argc, VALUE *argv, VALUE klass) {
      rb_raise(rb_eRuntimeError, "You cannot use #initialize on this class.");
      return Qnil;
    }

    VALUE wrapped() {
      if (!_value) {
        _value = Data_Wrap_Struct(klass(), base<T>::mark_dependencies, base<T>::dispose, this);
      }
      return _value;
    }

    virtual void mark() {
      if (_value) {
        rb_gc_mark(_value);
      }
    }

    virtual void mark_dependencies() {
      for (typename std::vector<gc_object *>::iterator it = _dependencies.begin(); it != _dependencies.end(); ++it) {
        (*it)->mark();
      }
    }

    virtual void dispose() {}
    virtual VALUE initialize(int argc, VALUE *argv) { return wrapped(); }

    virtual VALUE klass() {
      return Qnil;
    }

    virtual ~base() {}

    static T *unwrap(VALUE self) {
      T *obj = NULL;
      Data_Get_Struct(self, T, obj);
      return obj;
    }

    virtual std::vector<gc_object *> dependencies() {
      return _dependencies;
    }

    virtual void add_dependency(gc_object *dep) {
      _dependencies.push_back(dep);
    }

    virtual void remove_dependency(gc_object *dep) {
      _dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), dep), _dependencies.end());
    }

  protected:
    VALUE _value;

    std::vector<gc_object *> _dependencies;

    static T *object(void *ptr) {
      return static_cast<T *>(ptr);
    }

    static void mark_dependencies(void *ptr) {
      base::object(ptr)->mark_dependencies();
    }

    static void dispose(void *ptr) {
      delete base::object(ptr);
    }

    static void define(VALUE klass, bool allowNew) {
      if (allowNew) {
        rb_define_singleton_method(klass, "new", FGDB_METHOD(base<T>::new_instance), -1);
        rb_define_method(klass, "initialize", FGDB_METHOD(base<T>::initialize_instance), -1);
      }
      else {
        rb_define_singleton_method(klass, "new", FGDB_METHOD(base<T>::new_instance_not_allowed), -1);
        rb_define_method(klass, "initialize", FGDB_METHOD(base<T>::initialize_instance_not_allowed), -1);
      }
    }

    VALUE initialize_not_allowed() {
      rb_raise(rb_eRuntimeError, "You cannot use #new on this class.");
      return Qnil;
    }

  };
}

#endif
