require 'mkmf'

puts "PATH ------- " + Dir.pwd.to_s

dir_config '', 'filegdb'

have_library 'FileGDBAPI' or raise 'libFileGDBAPI not found'

$libs = append_library $libs, 'FileGDBAPI'

$LDFLAGS << " -Wl,-rpath,#{File.expand_path('./filegdb/lib')}"

create_makefile 'fgdb/fgdb'
