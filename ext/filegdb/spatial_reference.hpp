#ifndef __FGDB_SPATIAL_REFERENCE_HPP__
#define __FGDB_SPATIAL_REFERENCE_HPP__

#include "filegdb.hpp"
#include "base.hpp"

namespace filegdb {
  class spatial_reference : public base<spatial_reference> {
  public:
    spatial_reference() : base<spatial_reference>(), _spatialReference(new SpatialReference) {};
    static void define(VALUE module);

    static VALUE get_spatial_reference_text(VALUE self);
    static VALUE set_spatial_reference_text(VALUE self, VALUE srs);

    virtual VALUE klass();
    static VALUE _klass;

    SpatialReference &value() { return *_spatialReference; }

    virtual ~spatial_reference();

  private:
    SpatialReference *_spatialReference;
  };
}

#endif


