
#include "row.hpp"
#include "shape_buffer.hpp"

#define DATETIME_FORMAT "%Y-%m-%d %H:%M:%S"

namespace filegdb {

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

  return rb_str_new2(to_string(wvalue).c_str());
}

VALUE row::set_geometry(VALUE self, VALUE geometry) {
  row *row = unwrap(self);

  shape_buffer *shape = shape_buffer::unwrap(geometry);

  fgdbError hr = row->value().SetGeometry(shape->value());

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return shape->wrapped();
}

VALUE row::set_date(VALUE self, VALUE column, VALUE date) {
  CHECK_ARGUMENT_STRING(column)
  CHECK_ARGUMENT_STRING(date)

  row *row = unwrap(self);

  struct tm datetime;

  std::wstring wcolumn = to_wstring(RSTRING_PTR(column));

  if (strptime(RSTRING_PTR(date), DATETIME_FORMAT, &datetime) != NULL) {
    fgdbError hr = row->value().SetDate(wcolumn, datetime);

    if (FGDB_IS_FAILURE(hr)) {
      FGDB_RAISE_ERROR(hr);
      return Qnil;
    }
  } else {
    FGDB_FATAL("Date could not be parsed.");
    return Qnil;
  }

  return row->wrapped();
}

VALUE row::get_date(VALUE self, VALUE column) {
  CHECK_ARGUMENT_STRING(column)

  row *row = unwrap(self);

  std::wstring wcolumn = to_wstring(RSTRING_PTR(column));

  struct tm datetime;

  fgdbError hr = row->value().GetDate(wcolumn, datetime);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  char buffer[80];

  size_t length = strftime(buffer, 80, DATETIME_FORMAT, &datetime);

  if (length == 0) {
    FGDB_FATAL("Date could not be parsed.");
    return Qnil;
  }

  return rb_str_new2(buffer);
}

VALUE row::set_double(VALUE self, VALUE column, VALUE number) {
  CHECK_ARGUMENT_STRING(column)
  CHECK_ARGUMENT_FLOAT(number)

  row *row = unwrap(self);

  std::wstring wcolumn = to_wstring(RSTRING_PTR(column));

  fgdbError hr = row->value().SetDouble(wcolumn, NUM2DBL(number));

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return row->wrapped();
}

VALUE row::get_double(VALUE self, VALUE column) {
  CHECK_ARGUMENT_STRING(column)

  row *row = unwrap(self);

  std::wstring wcolumn = to_wstring(RSTRING_PTR(column));

  double result = 0;

  fgdbError hr = row->value().GetDouble(wcolumn, result);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_float_new(result);
}

VALUE row::set_integer(VALUE self, VALUE column, VALUE integer) {
  CHECK_ARGUMENT_STRING(column)
  CHECK_ARGUMENT_FIXNUM(integer)

  row *row = unwrap(self);

  std::wstring wcolumn = to_wstring(RSTRING_PTR(column));

  fgdbError hr = row->value().SetInteger(wcolumn, FIX2INT(integer));

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return row->wrapped();
}

VALUE row::get_integer(VALUE self, VALUE column) {
  CHECK_ARGUMENT_STRING(column)

  row *row = unwrap(self);

  std::wstring wcolumn = to_wstring(RSTRING_PTR(column));

  int32 result = 0;

  fgdbError hr = row->value().GetInteger(wcolumn, result);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return INT2NUM(result);
}

VALUE row::get_geometry(VALUE self) {
  FGDB_FATAL("Not implemented");
  return Qnil;
}

void row::define(VALUE module)
{
  row::_klass = rb_define_class_under(module, "Row", rb_cObject);
  base::define(row::_klass, false);
  rb_define_method(row::_klass, "set_string", FGDB_METHOD(row::set_string), 2);
  rb_define_method(row::_klass, "get_string", FGDB_METHOD(row::get_string), 1);
  rb_define_method(row::_klass, "set_geometry", FGDB_METHOD(row::set_geometry), 1);
  rb_define_method(row::_klass, "get_geometry", FGDB_METHOD(row::get_geometry), 0);
  rb_define_method(row::_klass, "set_date", FGDB_METHOD(row::set_date), 2);
  rb_define_method(row::_klass, "get_date", FGDB_METHOD(row::get_date), 1);
  rb_define_method(row::_klass, "set_double", FGDB_METHOD(row::set_double), 2);
  rb_define_method(row::_klass, "get_double", FGDB_METHOD(row::get_double), 1);
  rb_define_method(row::_klass, "set_integer", FGDB_METHOD(row::set_integer), 2);
  rb_define_method(row::_klass, "get_integer", FGDB_METHOD(row::get_integer), 1);
}

}
