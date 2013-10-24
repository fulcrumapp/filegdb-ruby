require 'spec_helper'

describe 'SpatialReference' do
  before(:each) do
    delete_database rescue nil
    @db = create_database
    @table = @db.create_table('', table_definition)
    @info = @table.get_field_information
    @srs = FileGDB::SpatialReference.new
  end

  after(:each) do
    @db.close if @db
    delete_database
  end

  it 'gets the spatial reference text' do
    @srs.get_spatial_reference_text.should eq('')
  end
end
