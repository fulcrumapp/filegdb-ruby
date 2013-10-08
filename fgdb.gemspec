# -*- encoding: utf-8 -*-
require File.expand_path('../lib/fgdb/version', __FILE__)

Gem::Specification.new do |gem|
  gem.authors       = ["Zac McCormick"]
  gem.email         = ["zac.mccormick@gmail.com"]
  gem.description   = %q{ESRI FileGDB bindings for ruby}
  gem.summary       = %q{ESRI FileGDB bindings for ruby. Currently contains native extensions for FileGDB API 1.3}
  gem.homepage      = "https://github.com/zhm/fgdb-ruby"

  gem.files         = `git ls-files`.split($\)
  gem.extensions    = ['ext/fgdb/extconf.rb']
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.name          = "fgdb"
  gem.require_paths = ["lib"]
  gem.version       = FGDB::VERSION

  gem.add_development_dependency 'rake',          ['>= 0']
  gem.add_development_dependency 'rake-compiler', ['>= 0']
  gem.add_development_dependency 'rspec',         ['>= 0']
end
