#ifndef __FGDB_SHAPE_BUFFER_BASE_HPP__
#define __FGDB_SHAPE_BUFFER_BASE_HPP__

#include "filegdb.hpp"
#include "base.hpp"

namespace filegdb {
  template <typename T, typename S>
  class shape_buffer_base : public base<T> {
  public:
    shape_buffer_base() : _shape_buffer(0) {};

    virtual ~shape_buffer_base() {
      if (_shape_buffer) {
        delete _shape_buffer;
        _shape_buffer = NULL;
      }
    }

    virtual VALUE initialize(int argc, VALUE *argv) {
      _shape_buffer = new S;
      return base<T>::wrapped();
    }

    S &value() { return *_shape_buffer; }
  protected:
    S *_shape_buffer;
  };
}

#endif


