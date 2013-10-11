require 'spec_helper'

describe "FileGDB" do
  before(:all) do
    delete_database rescue nil
  end

  after(:each) do
    delete_database rescue nil
  end

  after(:all) do
    delete_database rescue nil
  end

  it 'creates a new gdb' do
    db = create_database
    db.should_not be_nil
    db.close
  end

  it 'opens an existing gdb' do
    db = create_database
    db.close
    db = open_database
    db.should_not be_nil
    db.close
  end

  it 'creates a new table' do
    db = create_database
    table = db.create_table('', table_definition)
    table.should_not be_nil
    db.close
  end
end
