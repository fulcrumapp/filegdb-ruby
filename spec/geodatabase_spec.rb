require 'spec_helper'

describe "FileGDB" do
  before(:all) do
    delete_database rescue nil
  end

  before(:each) do
    @db = create_database
    @table = @db.create_table('', table_definition)
  end

  after(:each) do
    delete_database rescue nil
  end

  after(:all) do
    delete_database rescue nil
  end

  it 'gets the dataset types' do
    @db.get_dataset_types.should have(32).items
  end
end

