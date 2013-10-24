require 'mkmf'

filegdb_path = File.expand_path("#{File.dirname(__FILE__)}/filegdb")

dir_config '', File.join(filegdb_path, 'include'), File.join(filegdb_path, 'lib')

have_library 'FileGDBAPI' or raise 'libFileGDBAPI not found'

$libs = append_library $libs, 'FileGDBAPI'

$LDFLAGS << " -Wl,-rpath,#{File.join(filegdb_path, 'lib')}"

if RUBY_PLATFORM =~ /darwin12/
  # libFileGDBAPI requires GCC compilation because its C++ symbols are incompatible with LLVM 5.0
  #
  # To install GCC on OSX:
  #
  #   $ brew tap homebrew/versions
  #   $ brew install --enable-cxx gcc49
  #

  msg = <<-GCC


\e[31m
===========================================================================================================================
===========================================================================================================================

The filegdb gem requires GCC on OSX Mavericks because the C++ symbols in libFileGDBAPI.dylib are incompatible with LLVM 5.0

To install GCC on OSX:

   $ brew tap homebrew/versions
   $ brew install --enable-cxx gcc49

Note: Installing GCC through homebrew is safe and will not interfere with your Xcode installation.

Report installation bugs here: https://github.com/spatialnetworks/filegdb-ruby

===========================================================================================================================
===========================================================================================================================
\e[0m

GCC

  if `which gcc-4.9`.strip.length == 0
    puts msg
    exit
  end

  require 'rbconfig'
  RbConfig::MAKEFILE_CONFIG['CC']  = 'gcc-4.9'
  RbConfig::MAKEFILE_CONFIG['CXX'] = 'gcc-4.9'

  # remove -Wshorten-64-to-32 since it's incompatible with GCC
  $warnflags = $warnflags.gsub(/-Wshorten-64-to-32/, '')
end

create_makefile 'filegdb/filegdb'
