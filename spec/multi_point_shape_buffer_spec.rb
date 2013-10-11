require 'spec_helper'

NUM_POINTS = 3

describe 'MultiPointShapeBuffer' do
  before(:each) do
    @shape = FileGDB::MultiPointShapeBuffer.new
  end

  it 'sets up the geometry' do
    lambda { @shape.setup(8, NUM_POINTS) }.should_not raise_error
  end

  it 'gets the number of points' do
    @shape.setup(8, NUM_POINTS)
    @shape.get_num_points.should eq(NUM_POINTS)
  end

  it 'gets the points' do
    @shape.setup(8, NUM_POINTS)
    @shape.get_points.should have(3).items
  end

  it 'gets the z values' do
    @shape.setup(18, NUM_POINTS)
    @shape.z.should have(3).items
  end

  it 'gets the m values' do
    @shape.setup(18, NUM_POINTS)
    @shape.m.should have(3).items
  end

  it 'gets the id values' do
    @shape.setup(18, NUM_POINTS)
    lambda { @shape.id }.should raise_error
  end

  it 'gets the extent' do
    @shape.setup(18, NUM_POINTS)
    @shape.get_extent.should eq([0, 0, 0, 0])
  end

  it 'gets the z extent' do
    @shape.setup(18, NUM_POINTS)
    @shape.get_z_extent.should eq([0, 0])
  end

  it 'gets the m extent' do
    @shape.setup(18, NUM_POINTS)
    @shape.get_m_extent.should eq([0, 0])
  end
end
