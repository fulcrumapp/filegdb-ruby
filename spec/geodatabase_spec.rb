require 'spec_helper'

describe "FileGDB" do
  before(:all) do
    delete_database rescue nil
  end

  before(:each) do
    delete_database rescue nil
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

  it 'gets the dataset relationship types' do
    @db.get_dataset_relationship_types.should have(16).items
  end

  it 'gets the child datasets' do
    @db.get_child_datasets('', '').should have(0).items
  end
end

