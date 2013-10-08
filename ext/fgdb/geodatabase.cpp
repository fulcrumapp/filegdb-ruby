
#include "geodatabase.hpp"
#include "table.hpp"

namespace fgdb {

VALUE geodatabase::_klass = Qnil;

VALUE geodatabase::klass() {
  return geodatabase::_klass;
}

geodatabase::geodatabase()
:
  _gdb(NULL),
  _tables()
{
}

geodatabase::~geodatabase()
{
  for (std::vector<table *>::iterator it = _tables.begin(); it != _tables.end(); ++it) {
    delete *it;
  }

  if (_gdb) {
    CloseGeodatabase(*_gdb);
  }
}

VALUE geodatabase::initialize(int argc, VALUE *argv)
{
  rb_raise(rb_eRuntimeError, "You cannot use #new on FGDB. Use #create or #open");
  return Qnil;
}

void geodatabase::mark() {
}

VALUE geodatabase::create(VALUE klass, VALUE filename) {
  fgdbError hr;
  Geodatabase *gdb = new Geodatabase();
  std::wstring name = to_wstring(RSTRING_PTR(filename));

  hr = CreateGeodatabase(name, *gdb);

  if (FGDB_IS_FAILURE(hr)) {
    rb_raise(rb_eRuntimeError, fgdb_error_string(hr));
  }

  geodatabase *db = new geodatabase();

  db->_gdb = gdb;

  return db->wrapped();
}

VALUE geodatabase::open(VALUE klass, VALUE filename) {
  fgdbError hr;
  Geodatabase *gdb = new Geodatabase();
  std::wstring name = to_wstring(RSTRING_PTR(filename));

  hr = OpenGeodatabase(name, *gdb);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  geodatabase *db = new geodatabase();

  db->_gdb = gdb;

  return db->wrapped();
}

VALUE geodatabase::create_table(VALUE self, VALUE table_name, VALUE table_definition) {
  geodatabase *db = unwrap(self);

  fgdb::table *result = new fgdb::table(db);

  std::wstring name = to_wstring(RSTRING_PTR(table_name));
  std::string table_def = std::string(RSTRING_PTR(table_definition));

  fgdbError hr = db->_gdb->CreateTable(table_def, name, result->value());

  if (FGDB_IS_FAILURE(hr)) {
    delete result;
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return result->wrapped();
}


VALUE geodatabase::get_child_datasets(VALUE self, VALUE parent_path, VALUE dataset_type) {
  geodatabase *db = unwrap(self);

  std::vector<std::wstring> children;

  std::wstring wparent_name = to_wstring(RSTRING_PTR(parent_path));
  std::wstring wdataset_type = to_wstring(RSTRING_PTR(dataset_type));

  fgdbError hr = db->_gdb->GetChildDatasets(wparent_name, wdataset_type, children);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  VALUE result = rb_ary_new();

  for (std::vector<wstring>::iterator it = children.begin(); it != children.end(); ++it) {
    VALUE name = rb_str_new2(to_char_array(*it));
    rb_ary_push(result, name);
  }

  return result;
}

VALUE geodatabase::get_dataset_definition(VALUE self, VALUE path, VALUE dataset_type) {
  geodatabase *db = unwrap(self);

  std::string definition;
  std::wstring wpath = to_wstring(RSTRING_PTR(path));
  std::wstring wdataset_type = to_wstring(RSTRING_PTR(dataset_type));

  fgdbError hr = db->_gdb->GetDatasetDefinition(wpath, wdataset_type, definition);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_str_new2(definition.c_str());
}

void geodatabase::define(VALUE module)
{
  geodatabase::_klass = rb_define_class_under(module, "Geodatabase", rb_cObject);
  base::define(geodatabase::_klass);
  rb_define_singleton_method(geodatabase::_klass, "create", FGDB_METHOD(geodatabase::create), 1);
  rb_define_singleton_method(geodatabase::_klass, "open", FGDB_METHOD(geodatabase::open), 1);
  rb_define_method(geodatabase::_klass, "create_table", FGDB_METHOD(geodatabase::create_table), 2);
  rb_define_method(geodatabase::_klass, "get_child_datasets", FGDB_METHOD(geodatabase::get_child_datasets), 2);
  rb_define_method(geodatabase::_klass, "get_dataset_definition", FGDB_METHOD(geodatabase::get_dataset_definition), 2);
}

}

