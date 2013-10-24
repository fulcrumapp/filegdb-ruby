
#include "table.hpp"
#include "row.hpp"

namespace filegdb {

VALUE table::_klass = Qnil;

VALUE table::klass() {
  return table::_klass;
}

table::table(geodatabase *db)
: _db(db), _table(new Table)
{
}

table::~table() {
  if (_table) {
    delete _table;
    _table = NULL;
  }
}

VALUE table::create_row_object(VALUE self) {
  table *table = unwrap(self);

  filegdb::row *row = new filegdb::row(table);

  fgdbError hr = table->value().CreateRowObject(row->value());

  if (FGDB_IS_FAILURE(hr)) {
    delete row;
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return row->wrapped();
}

VALUE table::insert(VALUE self, VALUE row) {
  filegdb::table *table = unwrap(self);
  filegdb::row *newRow = filegdb::row::unwrap(row);

  fgdbError hr = table->value().Insert(newRow->value());

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return self;
}

VALUE table::get_definition(VALUE self) {
  filegdb::table *table = unwrap(self);

  std::string definition;

  fgdbError hr = table->value().GetDefinition(definition);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_str_new2(definition.c_str());
}

VALUE table::get_documentation(VALUE self) {
  filegdb::table *table = unwrap(self);

  std::string documentation;

  fgdbError hr = table->value().GetDocumentation(documentation);

  if (FGDB_IS_FAILURE(hr)) {
    FGDB_RAISE_ERROR(hr);
    return Qnil;
  }

  return rb_str_new2(documentation.c_str());
}

void table::define(VALUE module)
{
  table::_klass = rb_define_class_under(module, "Table", rb_cObject);
  base::define(table::_klass, false);
  rb_define_method(table::_klass, "create_row_object", FGDB_METHOD(table::create_row_object), 0);
  rb_define_method(table::_klass, "insert", FGDB_METHOD(table::insert), 1);
  rb_define_method(table::_klass, "get_definition", FGDB_METHOD(table::get_definition), 0);
  rb_define_method(table::_klass, "get_documentation", FGDB_METHOD(table::get_documentation), 0);
}

}


