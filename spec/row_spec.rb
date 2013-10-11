require 'spec_helper'

describe 'Row' do
  before(:each) do
    delete_database rescue nil
    @db = create_database
    @table = @db.create_table('', table_definition)
  end

  after(:each) do
    @db.close if @db
    delete_database
  end

  it 'creates a row object' do
    row = @table.create_row_object
    row.should_not be_nil
  end

  it 'sets a string attribute on a row' do
    row = @table.create_row_object
    lambda { row.set_string('string_field', 'a string value') }.should_not raise_error
  end

  it 'throws an error when setting a field that does not exist' do
    row = @table.create_row_object
    lambda { row.set_string('string_field_that_doesnt_exist', 'a string value') }.should raise_error
  end

  it 'retrieves a string field' do
    row = @table.create_row_object
    row.set_string('string_field', 'a string value')
    row.get_string('string_field').should eq('a string value')
  end

  it 'throws an error when retrieving a string field that does not exist' do
    row = @table.create_row_object
    row.set_string('string_field', 'a string value')
    lambda { row.get_string('string_field_that_doesnt_exist') }.should raise_error
  end

  it 'creates a point shape buffer using #new' do
    FileGDB::PointShapeBuffer.new.should_not be_nil
  end

  it 'can setup a geometry' do
    shape = FileGDB::PointShapeBuffer.new
    lambda { shape.setup(1) }.should_not raise_error
  end

  it 'throws an exception when setting up a point shape incorrectly' do
    shape = FileGDB::PointShapeBuffer.new
    lambda { shape.setup(2) }.should raise_error
  end

  it 'fetches the point object after setting it up' do
    shape = FileGDB::PointShapeBuffer.new
    shape.setup(1)
    shape.get_point.should be_instance_of(FileGDB::Point)
  end

  it 'sets the geometry of a point' do
    row = @table.create_row_object
    shape = FileGDB::PointShapeBuffer.new
    shape.setup(1)
    point = shape.get_point
    point.x = -82.23233;
    point.y = 27.457347347;
    lambda { row.set_geometry(shape) }.should_not raise_error
  end

  it 'throws an exception when setting up the geometry incorrectly' do
    row = @table.create_row_object
    lambda { row.set_geometry(nil) }.should raise_error
  end
end
