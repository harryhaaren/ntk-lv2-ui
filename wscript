#!/usr/bin/env python
import os
import shutil
from waflib import Logs
from waflib.extras import autowaf as autowaf

# Variables for 'waf dist'
APPNAME = 'eg-fltksynth.lv2'
VERSION = '1.0.0'

# Mandatory variables
top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_c')
    opt.load('compiler_cxx')
    autowaf.set_options(opt)

def configure(conf):
    conf.load('compiler_c')
    conf.load('compiler_cxx')
    autowaf.configure(conf)
    autowaf.display_header('Amp Configuration')

    if conf.env['MSVC_COMPILER']:
        conf.env.append_unique('CFLAGS', ['-TP', '-MD'])
    else:
        conf.env.append_unique('CFLAGS', '-std=c99')
        
    conf.env.append_unique('CXXFLAGS', '-std=c++0x')
    conf.env.append_unique('CXXFLAGS', '-fPIC')
    conf.env.append_unique('CXXFLAGS', '-g')

    if not autowaf.is_child():
        autowaf.check_pkg(conf, 'lv2core', uselib_store='LV2CORE')
        autowaf.check_pkg(conf, 'ntk', uselib_store='NTK')

    # Set env['pluginlib_PATTERN']
    pat = conf.env['cshlib_PATTERN']
    if pat.startswith('lib'):
        pat = pat[3:]
    conf.env['pluginlib_PATTERN'] = pat
    conf.env['pluginlib_EXT'] = pat[pat.rfind('.'):]

    autowaf.display_msg(conf, "LV2 bundle directory", conf.env['LV2DIR'])
    print('')

def build(bld):
    bundle = APPNAME

    # Build manifest.ttl by substitution (for portable lib extension)
    bld(features     = 'subst',
        source       = 'manifest.ttl.in',
        target       = '%s/%s' % (bundle, 'manifest.ttl'),
        install_path = '${LV2DIR}/%s' % bundle,
        LIB_EXT      = bld.env['pluginlib_EXT'])

    # Copy other data files to build bundle (build/eg-amp.lv2)
    for i in [ 'fltksynth.ttl' ]:
        bld(features     = 'subst',
            source       = i,
            target       = '%s/%s' % (bundle, i),
            install_path = '${LV2DIR}/%s' % bundle,
            LIB_EXT      = bld.env['pluginlib_EXT'])

    # Create a build environment that builds module-style library names
    # e.g. eg-amp.so instead of libeg-amp.so
    # Note for C++ you must set cxxshlib_PATTERN instead
    penv                   = bld.env.derive()
    penv['cshlib_PATTERN'] = bld.env['pluginlib_PATTERN']
    penv['cxxshlib_PATTERN'] = bld.env['pluginlib_PATTERN']

    includes = None
    if autowaf.is_child:
        includes = '../..'

    # Build plugin library
    obj = bld(features     = 'c cshlib',
              env          = penv,
              source       = 'sinsynth.c',
              name         = 'sinsynth',
              target       = '%s/fltksynth' % bundle,
              install_path = '${LV2DIR}/%s' % bundle,
              uselib       = 'LV2CORE',
              includes     = includes)
    
    # Build UI library
    obj = bld(features     = 'cxx cshlib',
              env          = penv,
              linkflags    = '-Wl,-z,nodelete', 
              source       = 'widget.cpp sinsynth_gui.cpp',
              name         = 'sinsynth_gui',
              target       = '%s/fltksynth_gui' % bundle,
              install_path = '${LV2DIR}/%s' % bundle,
              uselib       = 'LV2CORE NTK',
              includes     = includes)

