require 'spec_helper'

describe 'FieldInfo' do
  before(:each) do
    delete_database rescue nil
    @db = create_database
    @table = @db.create_table('', table_definition)
    @info = @table.get_field_information
  end

  after(:each) do
    @db.close if @db
    delete_database
  end

  it 'gets the field count' do
    @info.get_field_count.should eq(3)
  end

  it 'gets the field name' do
    @info.get_field_name(2).should eq('string_field')
  end
end


