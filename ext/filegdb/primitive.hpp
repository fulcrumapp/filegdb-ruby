#ifndef __FGDB_PRIMITIVE_HPP__
#define __FGDB_PRIMITIVE_HPP__

#include "filegdb.hpp"

namespace filegdb {
  template<typename T, typename K> class primitive : public base<K> {
  public:
    primitive(T *value) : _value(value) {}

    virtual ~primitive() {}

  protected:
    primitive() {}

    T *_value;
  };
}

#endif
