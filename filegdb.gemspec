# -*- encoding: utf-8 -*-
require File.expand_path('../lib/filegdb/version', __FILE__)

Gem::Specification.new do |gem|
  gem.authors       = ["Zac McCormick"]
  gem.email         = ["zac.mccormick@gmail.com"]
  gem.description   = %q{ESRI FileGDB bindings for ruby}
  gem.summary       = %q{ESRI FileGDB bindings for ruby. Currently contains native extensions for FileGDB API 1.4}
  gem.homepage      = "https://github.com/spatialnetworks/filegdb-ruby"
  gem.licenses      = ['BSD']

  gem.files         = `git ls-files`.split($\)
  gem.extensions    = ['ext/filegdb/extconf.rb']
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.name          = "filegdb"
  gem.require_paths = ['lib', 'ext']
  gem.version       = FileGDB::VERSION

  gem.add_development_dependency 'rake',          ['>= 0']
  gem.add_development_dependency 'rake-compiler', ['>= 0']
  gem.add_development_dependency 'rspec',         ['~> 2.14.1']
end
