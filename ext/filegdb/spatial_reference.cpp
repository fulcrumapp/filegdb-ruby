#include "spatial_reference.hpp"

namespace filegdb {

VALUE spatial_reference::_klass = Qnil;

VALUE spatial_reference::klass() {
  return spatial_reference::_klass;
}

spatial_reference::~spatial_reference() {
  if (_spatialReference) {
    delete _spatialReference;
    _spatialReference = NULL;
  }
}

VALUE spatial_reference::get_spatial_reference_text(VALUE self) {
  filegdb::spatial_reference *srs = unwrap(self);

  std::wstring text;

  fgdbError hr = srs->value().GetSpatialReferenceText(text);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_str_new2(to_string(text).c_str());
}

VALUE spatial_reference::set_spatial_reference_text(VALUE self, VALUE srs) {
  CHECK_ARGUMENT_STRING(srs);

  filegdb::spatial_reference *reference = unwrap(self);

  fgdbError hr = reference->value().SetSpatialReferenceText(to_wstring(RSTRING_PTR(srs)));

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return Qnil;
}

void spatial_reference::define(VALUE module)
{
  spatial_reference::_klass = rb_define_class_under(module, "SpatialReference", rb_cObject);
  base::define(spatial_reference::_klass, true);
  rb_define_method(spatial_reference::_klass, "get_spatial_reference_text", FGDB_METHOD(spatial_reference::get_spatial_reference_text), 0);
  rb_define_method(spatial_reference::_klass, "set_spatial_reference_text", FGDB_METHOD(spatial_reference::set_spatial_reference_text), 1);
}

}




