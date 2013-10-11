
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

void table::define(VALUE module)
{
  table::_klass = rb_define_class_under(module, "Table", rb_cObject);
  base::define(table::_klass, false);
  rb_define_method(table::_klass, "create_row_object", FGDB_METHOD(table::create_row_object), 0);
  rb_define_method(table::_klass, "insert", FGDB_METHOD(table::insert), 1);
}

}


