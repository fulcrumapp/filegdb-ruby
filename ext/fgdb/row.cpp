
#include "row.hpp"
#include "shape_buffer.hpp"

namespace fgdb {

VALUE row::_klass = Qnil;

VALUE row::klass() {
  return row::_klass;
}

row::row(table *table)
: _table(table), _row(new Row)
{
}

row::~row() {
  if (_row) {
    delete _row;
    _row = NULL;
  }
}

VALUE row::initialize(int argc, VALUE *argv)
{
  rb_raise(rb_eRuntimeError, "You cannot use #new on FGDB::Row. You must use the Table class to access row.");
  return Qnil;
}

VALUE row::set_string(VALUE self, VALUE column, VALUE value) {
  row *row = unwrap(self);

  std::wstring wcolumn = to_wstring(RSTRING_PTR(column));
  std::wstring wvalue = to_wstring(RSTRING_PTR(value));

  fgdbError hr = row->value().SetString(wcolumn, wvalue);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return row->_value;
}

VALUE row::get_string(VALUE self, VALUE column) {
  row *row = unwrap(self);

  std::wstring wcolumn = to_wstring(RSTRING_PTR(column));
  std::wstring wvalue;

  fgdbError hr = row->value().GetString(wcolumn, wvalue);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_str_new2(to_char_array(wvalue));
}

VALUE row::set_geometry(VALUE self, VALUE geometry) {
  row *row = unwrap(self);

  shape_buffer *shape = shape_buffer::unwrap(geometry);

  fgdbError hr = row->value().SetGeometry(shape->value());

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return shape->rvalue();
}

VALUE row::get_geometry(VALUE self) {
  FGDB_FATAL("Not implemented");
  return Qnil;
}

void row::define(VALUE module)
{
  row::_klass = rb_define_class_under(module, "Row", rb_cObject);
  base::define(row::_klass);
  rb_define_method(row::_klass, "set_string", FGDB_METHOD(row::set_string), 2);
  rb_define_method(row::_klass, "get_string", FGDB_METHOD(row::get_string), 1);
  rb_define_method(row::_klass, "set_geometry", FGDB_METHOD(row::set_geometry), 1);
  rb_define_method(row::_klass, "get_geometry", FGDB_METHOD(row::get_geometry), 0);
}

}
