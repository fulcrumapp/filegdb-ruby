require 'spec_helper'

describe 'PointShapeBuffer' do
  before(:each) do
    @shape = FileGDB::PointShapeBuffer.new
  end

  it 'gets the z value' do
    @shape.setup(9)
    @shape.z.should eq(0.0)
  end

  it 'sets the z value' do
    @shape.setup(9)
    @shape.z = 10.0
    @shape.z.should eq(10.0)
  end

  it 'gets the m value' do
    @shape.setup(11)
    @shape.m.should eq(0.0)
  end

  it 'sets the m value' do
    @shape.setup(11)
    @shape.m = 10.0
    @shape.m.should eq(10.0)
  end

  it 'gets the id value' do
    @shape.setup(11)
    lambda { @shape.id }.should raise_error
  end

  it 'sets the id value' do
    @shape.setup(11)
    lambda { @shape.id = 1 }.should raise_error
  end
end
