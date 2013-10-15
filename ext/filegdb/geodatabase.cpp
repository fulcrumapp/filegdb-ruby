
#include "geodatabase.hpp"
#include "table.hpp"

namespace filegdb {

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

VALUE geodatabase::delete_database(VALUE klass, VALUE filename) {
  fgdbError hr;
  std::wstring name = to_wstring(RSTRING_PTR(filename));

  hr = DeleteGeodatabase(name);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return Qnil;
}

VALUE geodatabase::close(VALUE self) {
  fgdbError hr;

  geodatabase *db = unwrap(self);

  hr = CloseGeodatabase(*db->_gdb);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  db->_value = NULL;

  return Qnil;
}

VALUE geodatabase::create_table(VALUE self, VALUE table_name, VALUE table_definition) {
  geodatabase *db = unwrap(self);

  filegdb::table *result = new filegdb::table(db);

  std::wstring name = to_wstring(RSTRING_PTR(table_name));
  std::string table_def = std::string(RSTRING_PTR(table_definition));

  fgdbError hr = db->_gdb->CreateTable(table_def, name, result->value());

  if (FGDB_IS_FAILURE(hr)) {
    delete result;
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  db->add_dependency(result);

  return result->wrapped();
}

VALUE geodatabase::create_feature_dataset(VALUE self, VALUE featureDatasetDefinition) {
  CHECK_ARGUMENT_STRING(featureDatasetDefinition);

  geodatabase *db = unwrap(self);

  fgdbError hr = db->_gdb->CreateFeatureDataset(std::string(RSTRING_PTR(featureDatasetDefinition)));

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return Qnil;
}

VALUE geodatabase::open_table(VALUE self, VALUE table_name) {
  geodatabase *db = unwrap(self);

  table *result = new filegdb::table(db);

  std::wstring name = to_wstring(RSTRING_PTR(table_name));

  fgdbError hr = db->_gdb->OpenTable(name, result->value());

  if (FGDB_IS_FAILURE(hr)) {
    delete result;
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  db->add_dependency(result);

  return result->wrapped();
}

VALUE geodatabase::close_table(VALUE self, VALUE tableObject) {
  geodatabase *db = unwrap(self);
  table *t = table::unwrap(tableObject);

  fgdbError hr = db->_gdb->CloseTable(t->value());

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  db->remove_dependency(t);

  return Qnil;
}

VALUE geodatabase::move(VALUE self, VALUE parentPath, VALUE newParentPath) {
  CHECK_ARGUMENT_STRING(parentPath);
  CHECK_ARGUMENT_STRING(newParentPath);

  geodatabase *db = unwrap(self);

  std::wstring wparentPath = to_wstring(RSTRING_PTR(parentPath));
  std::wstring wnewParentPath = to_wstring(RSTRING_PTR(newParentPath));

  fgdbError hr = db->_gdb->Move(wparentPath, wnewParentPath);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return Qnil;
}

VALUE geodatabase::delete_dataset(VALUE self, VALUE path, VALUE datasetType) {
  CHECK_ARGUMENT_STRING(path);
  CHECK_ARGUMENT_STRING(datasetType);

  geodatabase *db = unwrap(self);

  std::wstring wpath = to_wstring(RSTRING_PTR(path));
  std::wstring wdatasetType = to_wstring(RSTRING_PTR(datasetType));

  fgdbError hr = db->_gdb->Delete(wpath, wdatasetType);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return Qnil;
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

VALUE geodatabase::get_dataset_documentation(VALUE self, VALUE path, VALUE datasetType) {
  CHECK_ARGUMENT_STRING(path);
  CHECK_ARGUMENT_STRING(datasetType);

  geodatabase *db = unwrap(self);

  std::string documentation;
  std::wstring wpath = to_wstring(RSTRING_PTR(path));
  std::wstring wdatasetType = to_wstring(RSTRING_PTR(datasetType));

  fgdbError hr = db->_gdb->GetDatasetDocumentation(wpath, wdatasetType, documentation);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_str_new2(documentation.c_str());
}

VALUE geodatabase::rename(VALUE self, VALUE path, VALUE datasetType, VALUE newName) {
  CHECK_ARGUMENT_STRING(path);
  CHECK_ARGUMENT_STRING(datasetType);
  CHECK_ARGUMENT_STRING(newName);

  geodatabase *db = unwrap(self);

  std::wstring wpath = to_wstring(RSTRING_PTR(path));
  std::wstring wdatasetType = to_wstring(RSTRING_PTR(datasetType));
  std::wstring wnewName = to_wstring(RSTRING_PTR(newName));

  fgdbError hr = db->_gdb->Rename(wpath, wdatasetType, wnewName);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return Qnil;
}

VALUE geodatabase::get_child_dataset_definitions(VALUE self, VALUE parentPath, VALUE datasetType) {
  CHECK_ARGUMENT_STRING(parentPath);
  CHECK_ARGUMENT_STRING(datasetType);

  geodatabase *db = unwrap(self);

  std::vector<std::string> definitions;
  std::wstring wparentPath = to_wstring(RSTRING_PTR(parentPath));
  std::wstring wdatasetType = to_wstring(RSTRING_PTR(datasetType));

  fgdbError hr = db->_gdb->GetChildDatasetDefinitions(wparentPath, wdatasetType, definitions);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  VALUE result = rb_ary_new();

  for (typename std::vector<string>::iterator it = definitions.begin(); it != definitions.end(); ++it) {
    rb_ary_push(result, rb_str_new2((*it).c_str()));
  }

  return result;
}

VALUE geodatabase::get_related_dataset_definitions(VALUE self, VALUE path, VALUE relType, VALUE datasetType) {
  CHECK_ARGUMENT_STRING(path);
  CHECK_ARGUMENT_STRING(relType);
  CHECK_ARGUMENT_STRING(datasetType);

  geodatabase *db = unwrap(self);

  std::vector<std::string> definitions;
  std::wstring wpath = to_wstring(RSTRING_PTR(path));
  std::wstring wrelType = to_wstring(RSTRING_PTR(relType));
  std::wstring wdatasetType = to_wstring(RSTRING_PTR(datasetType));

  fgdbError hr = db->_gdb->GetRelatedDatasetDefinitions(wpath, wrelType, wdatasetType, definitions);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  VALUE result = rb_ary_new();

  for (typename std::vector<string>::iterator it = definitions.begin(); it != definitions.end(); ++it) {
    rb_ary_push(result, rb_str_new2((*it).c_str()));
  }

  return result;
}

VALUE geodatabase::get_dataset_types(VALUE self) {
  geodatabase *db = unwrap(self);

  std::vector<std::wstring> datasetTypes;

  fgdbError hr = db->_gdb->GetDatasetTypes(datasetTypes);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  VALUE result = rb_ary_new();

  for (typename std::vector<wstring>::iterator it = datasetTypes.begin(); it != datasetTypes.end(); ++it) {
    rb_ary_push(result, rb_str_new2(to_char_array(*it)));
  }

  return result;
}

VALUE geodatabase::get_dataset_relationship_types(VALUE self) {
  geodatabase *db = unwrap(self);

  std::vector<std::wstring> datasetTypes;

  fgdbError hr = db->_gdb->GetDatasetRelationshipTypes(datasetTypes);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  VALUE result = rb_ary_new();

  for (typename std::vector<wstring>::iterator it = datasetTypes.begin(); it != datasetTypes.end(); ++it) {
    rb_ary_push(result, rb_str_new2(to_char_array(*it)));
  }

  return result;
}

VALUE geodatabase::get_related_datasets(VALUE self, VALUE path, VALUE relType, VALUE datasetType) {
  CHECK_ARGUMENT_STRING(path);
  CHECK_ARGUMENT_STRING(relType);
  CHECK_ARGUMENT_STRING(datasetType);

  geodatabase *db = unwrap(self);

  std::vector<std::wstring> datasets;
  std::wstring wpath = to_wstring(RSTRING_PTR(path));
  std::wstring wrelType = to_wstring(RSTRING_PTR(relType));
  std::wstring wdatasetType = to_wstring(RSTRING_PTR(datasetType));

  fgdbError hr = db->_gdb->GetRelatedDatasets(wpath, wrelType, wdatasetType, datasets);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  VALUE result = rb_ary_new();

  for (typename std::vector<wstring>::iterator it = datasets.begin(); it != datasets.end(); ++it) {
    rb_ary_push(result, rb_str_new2(to_char_array(*it)));
  }

  return result;
}

VALUE geodatabase::create_domain(VALUE self, VALUE domainDefinition) {
  CHECK_ARGUMENT_STRING(domainDefinition);

  geodatabase *db = unwrap(self);

  fgdbError hr = db->_gdb->CreateDomain(std::string(RSTRING_PTR(domainDefinition)));

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return Qnil;
}

void geodatabase::define(VALUE module)
{
  geodatabase::_klass = rb_define_class_under(module, "Geodatabase", rb_cObject);
  base::define(geodatabase::_klass, false);
  rb_define_singleton_method(geodatabase::_klass, "create", FGDB_METHOD(geodatabase::create), 1);
  rb_define_singleton_method(geodatabase::_klass, "open", FGDB_METHOD(geodatabase::open), 1);
  rb_define_singleton_method(geodatabase::_klass, "delete", FGDB_METHOD(geodatabase::delete_database), 1);
  rb_define_method(geodatabase::_klass, "close", FGDB_METHOD(geodatabase::close), 0);
  rb_define_method(geodatabase::_klass, "create_table", FGDB_METHOD(geodatabase::create_table), 2);
  rb_define_method(geodatabase::_klass, "open_table", FGDB_METHOD(geodatabase::open_table), 1);
  rb_define_method(geodatabase::_klass, "close_table", FGDB_METHOD(geodatabase::close_table), 1);
  rb_define_method(geodatabase::_klass, "get_child_datasets", FGDB_METHOD(geodatabase::get_child_datasets), 2);
  rb_define_method(geodatabase::_klass, "get_dataset_definition", FGDB_METHOD(geodatabase::get_dataset_definition), 2);
  rb_define_method(geodatabase::_klass, "get_dataset_documentation", FGDB_METHOD(geodatabase::get_dataset_documentation), 2);
  rb_define_method(geodatabase::_klass, "get_child_dataset_definitions", FGDB_METHOD(geodatabase::get_child_dataset_definitions), 2);
  rb_define_method(geodatabase::_klass, "get_related_dataset_definitions", FGDB_METHOD(geodatabase::get_child_dataset_definitions), 3);
  rb_define_method(geodatabase::_klass, "get_dataset_types", FGDB_METHOD(geodatabase::get_dataset_types), 0);
  rb_define_method(geodatabase::_klass, "get_dataset_relationship_types", FGDB_METHOD(geodatabase::get_dataset_relationship_types), 0);
  rb_define_method(geodatabase::_klass, "get_related_datasets", FGDB_METHOD(geodatabase::get_related_datasets), 3);
  rb_define_method(geodatabase::_klass, "rename", FGDB_METHOD(geodatabase::rename), 3);
  rb_define_method(geodatabase::_klass, "move", FGDB_METHOD(geodatabase::move), 2);
  rb_define_method(geodatabase::_klass, "create_feature_dataset", FGDB_METHOD(geodatabase::create_feature_dataset), 1);
  rb_define_method(geodatabase::_klass, "delete", FGDB_METHOD(geodatabase::delete_dataset), 2);
  rb_define_method(geodatabase::_klass, "create_domain", FGDB_METHOD(geodatabase::create_domain), 1);
}

}

