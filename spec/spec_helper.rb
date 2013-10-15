require 'filegdb'

RSpec.configure do |config|
  config.color_enabled = true
  config.tty = true
  config.formatter = :documentation
end

TEST_FILE_NAME = 'testfile.gdb'

def data_directory
  File.join(File.dirname(__FILE__), 'data')
end

def table_definition
  File.read(File.join(data_directory, 'table_definition.xml'))
end

def feature_dataset_definition
  File.read(File.join(data_directory, 'feature_dataset_definition.xml'))
end

def create_database
  FileGDB::Geodatabase.create(TEST_FILE_NAME)
end

def open_database
  FileGDB::Geodatabase.open(TEST_FILE_NAME)
end

def delete_database
  FileGDB::Geodatabase.delete(TEST_FILE_NAME)
end
