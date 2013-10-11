require 'spec_helper'

NUM_POINTS = 3

describe 'MultiPointShapeBuffer' do
  before(:each) do
    @shape = FileGDB::MultiPointShapeBuffer.new
  end

  it 'sets up the geometry' do
    lambda { @shape.setup(8, NUM_POINTS) }.should_not raise_error
  end
end
