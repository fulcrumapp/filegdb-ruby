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

  it 'gets the related datasets' do
    @db.get_related_datasets('', '', '').should have(0).items
  end

  it 'gets the dataset definition' do
    @db.get_dataset_definition('\\TestTable', 'Table').length.should eq(7188)
  end

  it 'gets the dataset documentation' do
    lambda { @db.get_dataset_documentation('\\TestTable', 'Table') }.should raise_error
  end

  it 'gets the child dataset definitions' do
    @db.get_child_dataset_definitions('\\TestTable', 'Table').should have(0).items
  end

  it 'gets the related dataset definitions' do
    @db.get_related_dataset_definitions('\\TestTable', '', 'Table').should have(0).items
  end

  it 'creates a feature dataset' do
    lambda { @db.create_feature_dataset(feature_dataset_definition) }.should_not raise_error
  end

  it 'closes a table' do
    lambda { @db.close_table(@table) }.should_not raise_error
  end

  it 'renames a table' do
    lambda { @db.rename('\\TestTable', 'Table', 'TestTableNew') }.should_not raise_error
    @db.get_dataset_definition('\\TestTableNew', 'Table').length.should eq(5839)
  end

  it 'moves a table' do
    lambda { @db.move('TestTable', 'TestTable2') }.should raise_error
  end

  it 'deletes a table' do
    @db.close_table(@table)
    lambda { @db.delete('\\TestTable', 'Table') }.should_not raise_error
  end

  it 'creates a domain' do
    lambda { @db.create_domain(domain_definition) }.should_not raise_error
  end

  it 'alters a domain' do
    lambda { @db.create_domain(domain_definition) }.should_not raise_error
    lambda { @db.alter_domain(domain_definition_altered) }.should_not raise_error
  end

  it 'deletes a domain' do
    lambda { @db.create_domain(domain_definition) }.should_not raise_error
    lambda { @db.delete_domain('RoadSurfaceType') }.should_not raise_error
  end

  it 'fails to delete a domain that does not exist' do
    lambda { @db.create_domain(domain_definition) }.should_not raise_error
    lambda { @db.delete_domain('ThisDomainDoesNotExist') }.should raise_error
  end

  it 'gets the domain definition' do
    lambda { @db.create_domain(domain_definition) }.should_not raise_error
    @db.get_domain_definition('RoadSurfaceType').should_not be_nil
  end

  it 'fails to get the domain definition when the domain does not exist' do
    lambda { @db.get_domain_definition('ThisDomainDoesNotExist') }.should raise_error
  end

  it 'gets the query name of a table' do
    @db.get_query_name('TestTable').should eq('TestTable')
  end
end
