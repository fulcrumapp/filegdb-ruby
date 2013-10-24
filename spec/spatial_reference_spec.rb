require 'spec_helper'

describe 'SpatialReference' do
  before(:each) do
    delete_database rescue nil
    @db = create_database
    @table = @db.create_table('', table_definition)
    @info = @table.get_field_information
    @srs = FileGDB::SpatialReference.new
    @valid_srs = 'GEOGCS["GCS_WGS_1984",DATUM["D_WGS_1984",SPHEROID["WGS_1984",6378137,298.257223563]],PRIMEM["Greenwich",0],UNIT["Degree",0.017453292519943295]]'
  end

  after(:each) do
    @db.close if @db
    delete_database
  end

  it 'gets the spatial reference text' do
    @srs.get_spatial_reference_text.should eq('')
  end

  it 'sets the spatial reference text' do
    lambda { @srs.set_spatial_reference_text(@valid_srs) }.should_not raise_error
    @srs.get_spatial_reference_text.should eq(@valid_srs)
  end
end
