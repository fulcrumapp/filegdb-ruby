#!/usr/bin/env rake
require 'rubygems'
require 'bundler'
require 'bundler/gem_tasks'
require 'rake/testtask'
require 'rake'
require 'rake/extensiontask'
require 'rspec/core'
require 'rspec/core/rake_task'

Bundler.setup

Rake::ExtensionTask.new('fgdb') do |ext|
  ext.name = 'fgdb'
  ext.lib_dir = "lib/fgdb"
end

RSpec::Core::RakeTask.new(:spec) do |spec|
  Rake::Task['compile'].invoke
  spec.pattern = FileList['spec/**/*_spec.rb']
end

task :default => :spec
