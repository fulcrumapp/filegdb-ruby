require 'spec_helper'

describe 'Table' do
  before(:each) do
    delete_database rescue nil
    @db = create_database
    @table = @db.create_table('', table_definition)
  end

  after(:each) do
    @db.close if @db
    delete_database
  end

  it 'gets the definition' do
    @table.get_definition.should_not be_nil
  end

  it 'gets the documentation' do
    @table.get_documentation.should eq('')
  end

  it 'sets the documentation' do
    @table.set_documentation('Table Documentation')
    @table.get_documentation.should eq('Table Documentation')
  end
end

