import glob
import os

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
from sys import platform

__version__ = '0.0.16'

dir_path = os.path.dirname(os.path.realpath(__file__))
istravis = os.environ.get('TRAVIS') == 'true'


from os.path import expanduser


arch_x64=sys.maxsize > 0x100000000
triplet='x64-windows'
gdal_lib_name='gdal'
if not arch_x64:
    triplet='x86-windows'


def pip_install(package_name):
    subprocess.call(
        [sys.executable, '-m', 'pip', 'install', package_name]
    )

gdal_exist = False
vcpkg_root = None
def get_vcpkg_dir_for_win():
    home = expanduser("~")
    file=os.path.join(home, 'AppData', 'Local', 'vcpkg', 'vcpkg.path.txt')
    if os.path.isfile(file):
        f = open(file, "r")
        firstline=f.readline()
        print('vcpkg directory might be in',firstline)
        if os.path.isdir(firstline):
            vcpkg_root=os.path.normpath(firstline)
            vcpkg_libs=os.path.join(vcpkg_root, 'installed', triplet, 'lib')
            if os.path.isfile(os.path.join(vcpkg_libs, 'gdal.lib')):
                gdal_exist=True
                print("setup could find gdal library in ",os.path.join(vcpkg_libs, 'gdal.lib'))
                return vcpkg_root
            else:
                raise RuntimeError('Can not find gdal.lib in:'+vcpkg_libs+' you have a '+triplet+' Python version so try to install gdal using following command: vcpkg install gdal: '+triplet)
        else:
           raise RuntimeError('Can not find gdal.lib in:'+vcpkg_libs+' you have a '+triplet+' Python version so try to install gdal using following command: vcpkg install gdal: '+triplet)
            
    else:
        raise RuntimeError('This package can be installed easily using vcpkg on windows. So try to install vcpkg on windows and then install gdal library using vcpkg install gdal:x86-windows or vcpkg install gdal:x64-windows. Don\'t forget to call vcpkg integrate install as well.' )


class get_pybind_include(object):
    """Helper class to determine the pybind11 include path

    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)

import os, fnmatch
def find(pattern, path):
    result = []
    for root, dirs, files in os.walk(path):
        for name in files:
            if fnmatch.fnmatch(name, pattern):
                result.append(os.path.join(root, name))
    return result

windows_dll_list = []
def get_vcpkg_dll_lists():
    list = ['expat.dll','geos.dll','geos_c.dll','libcharset.dll','libcurl.dll','LIBEAY32.dll','libiconv.dll','libpng16.dll','libpq.dll','libxml2.dll','lzma.dll','openjp2.dll','sqlite3.dll','SSLEAY32.dll','webp.dll','zlib1.dll','shp.dll']

    vcpkg_bin=os.path.join(vcpkg_root, 'installed', triplet, 'bin')
    gdal_dll=find('gdal*.dll', vcpkg_bin)
    if len(gdal_dll)!=1:
        return False
    else:
        list.append(gdal_dll[0])
        for dll in list:
            if os.path.isfile(os.path.join(vcpkg_bin, dll)):
                windows_dll_list.append(os.path.join(vcpkg_bin, dll))
            else:
                print("Cannot find  ",dll)


print(sys.version,"is version of python")
if sys.version_info > (3, 6):
    with open("README.md", "r",encoding='utf-8') as fh:
        long_description = fh.read()
else:
        long_description =""



lib_directory=''
include_directory=''
if platform == "linux" or platform == "linux2":
    if os.path.isdir('/usr/include/gdal'):
        include_directory='/usr/include/gdal'
        gdal_lib_name='gdal'
else:
    gdal_lib_name='gdal'
    vcpkg_root=get_vcpkg_dir_for_win()
    get_vcpkg_dll_lists()
    lib_directory=os.path.join(vcpkg_root, 'installed', triplet, 'lib')
    include_directory=os.path.join(vcpkg_root, 'installed', triplet, 'include')
    print(sys.prefix)

sources = []
sources += glob.glob(os.path.join(dir_path, 'src', 'lib',  '*.cpp'))
sources += glob.glob(os.path.join(dir_path, 'src',  '*.cpp'))
sources += glob.glob(os.path.join(dir_path, 'src', 'lib',  '*.c'))

# print(sources)
ext_modules = [
    Extension(
        'pydggrid',
        sources,
        include_dirs=[
            os.path.join(dir_path, 'src', 'lib', ),
            os.path.join(dir_path, 'src' ),
            # FIXME: install issue for venv
            '/usr/local/include/python3.6',
            '/usr/include',
            # Path to pybind11 headers
            get_pybind_include(),
            include_directory,
            get_pybind_include(user=True)
        ],
        libraries =[gdal_lib_name,'gdal','shp'],
        library_dirs =[lib_directory,'/usr/lib'],
	    #runtime_library_dirs = ['/usr/lib'],
	    # extra_link_args=['-lgdal','-lshp','shp.lib','gdal.lib'],
        language='c++'
    ),
]


# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14] compiler flag.

    The c++14 is prefered over c++11 (when it is available).
    """
    if has_flag(compiler, '-std=c++14'):
        return '-std=c++14'
    elif has_flag(compiler, '-std=c++11'):
        return '-std=c++11'
    else:
        raise RuntimeError('Unsupported compiler -- at least C++11 support '
                           'is needed!')


import distutils.ccompiler
import subprocess

compiler_name = distutils.ccompiler.get_default_compiler()


class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }

    if sys.platform == 'darwin':
        c_opts['unix'] += ['-stdlib=libc++', '-mmacosx-version-min=10.7']

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])

        # if compiler_name=='mingw32':
        # print (compiler_name)

        if ct == 'unix':
            opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
            opts.append(cpp_flag(self.compiler))
            opts.append('-Wno-unknown-pragmas')


            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
            opts.append('-D_hypot=hypot')
            # opts.append('/w')
            opts.append('/Y-')
            # opts.append('/MT')
            # opts.append('/c')
            opts.append('/D_USE_MATH_DEFINES')
            opts.append('/wd4996')
        for ext in self.extensions:
            ext.extra_compile_args = opts
        #opts.append('-L/usr/lib -lgdal -l/usr/lib/libshp.so -llibshp.so -lshp')

        build_ext.build_extensions(self)


setup(
    name='pydggrid',
    version=__version__,
    author='Majid Hojati',
    author_email='asd56yu@gmail.com',
    url='https://github.com/am2222/pydggrid',
    description='Python wrapper for DGGRID',
    data_files=[('',windows_dll_list)],
    long_description=long_description,
    long_description_content_type="text/markdown",
    ext_modules=ext_modules,
    install_requires=['pybind11>=2.2'],
    setup_requires=['pybind11>=2.2'],
    cmdclass={'build_ext': BuildExt},
    zip_safe=False,
    classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'License :: OSI Approved :: Academic Free License (AFL)',
        'Programming Language :: C++ ',
        'Topic :: Scientific/Engineering :: GIS',
    ],
    keywords='GIS, DGGS'
    # test_suite='tests'

)
