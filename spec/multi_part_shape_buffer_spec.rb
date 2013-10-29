require 'spec_helper'

NUM_POINTS = 3
NUM_PARTS  = 1

describe 'MultiPartShapeBuffer' do
  before(:each) do
    @shape = FileGDB::MultiPartShapeBuffer.new
    @shape.setup(15, NUM_PARTS, NUM_POINTS)
  end

  it 'sets up the geometry' do
    lambda { @shape.setup(5, NUM_POINTS, NUM_PARTS) }.should_not raise_error
  end

  it 'gets the number of points' do
    @shape.get_num_points.should eq(NUM_POINTS)
  end

  it 'gets the number of parts' do
    @shape.get_num_parts.should eq(NUM_PARTS)
  end

  it 'gets the parts' do
    @shape.get_parts.should have(1).item
  end

  it 'sets the parts' do
    parts = @shape.get_parts
    parts[0].value = 10
    @shape.get_parts[0].value.should eq(10)
  end

  it 'gets the points' do
    @shape.get_points.should have(3).items
  end

  it 'gets the z values' do
    @shape.z.should have(3).items
  end

  it 'gets the m values' do
    @shape.m.should have(3).items
  end

  it 'gets the id values' do
    lambda { @shape.id }.should raise_error
  end

  it 'gets the extent' do
    @shape.get_extent.should eq([0, 0, 0, 0])
  end

  it 'gets the z extent' do
    @shape.get_z_extent.should eq([0, 0])
  end

  it 'gets the m extent' do
    @shape.get_m_extent.should eq([0, 0])
  end

  it 'calculates the extent' do
    lambda { @shape.calculate_extent }.should_not raise_error
  end
end

