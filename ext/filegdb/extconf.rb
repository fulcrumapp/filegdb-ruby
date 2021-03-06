require 'mkmf'

filegdb_path = File.expand_path("#{File.dirname(__FILE__)}/filegdb")

dir_config '', File.join(filegdb_path, 'include'), File.join(filegdb_path, 'lib')

have_library 'FileGDBAPI' or raise 'libFileGDBAPI not found'

$libs = append_library $libs, 'FileGDBAPI'

$CXXFLAGS += " -D_GLIBCXX_USE_CXX11_ABI=0 "

if `ld --help | grep disable-new-dtags | wc -l`.strip == '1'
  $LDFLAGS << " -Wl,--disable-new-dtags"
end

$LDFLAGS << " -Wl,-rpath,#{File.join(filegdb_path, 'lib')}"

create_makefile 'filegdb/filegdb'
