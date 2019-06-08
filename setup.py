import glob
import os

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
from sys import platform

__version__ = '0.0.14'

dir_path = os.path.dirname(os.path.realpath(__file__))
istravis = os.environ.get('TRAVIS') == 'true'


boost_directory = 'boost_dir'
boost_directory_value = os.environ.get( boost_directory, None )

if boost_directory_value is not None or istravis:
    sys.stderr.write( "Using '%s=%s' environment variable!\n" % (
            boost_directory, boost_directory_value ) )
else:
    if platform == "linux" or platform == "linux2":
        boost_directory_value='/home/usr/include/boost/'
    else:
        raise RuntimeError('Please specify Boost directory. It must be defined as '
                       'boost_dir=/home/usr/include/boost/ pip install pydggrid on Linux systems '
                       'and set "boost_dir=C:/Boost/include/" && pip install. The boost version must be higher than boost 1.70.0')
# os.environ["CC"] = "g++-4.7"
# os.environ["CXX"] = "g++-4.7"
# os.environ["THEANO_FLAGS"] = 'gcc.cxxflags="-D_hypot=hypot"'



from setuptools.command.install import install
def get_boost_include():
    if istravis:
        return '/home/travis/boost_1_70_0/'
    else:
        # if os.name=='nt':
        #     #     running on windows
        #     root = 'C:/Boost/include/'
        #     dirlist = [item for item in os.listdir(root) if os.path.isdir(os.path.join(root, item))]
        #     for d in dirlist:
        #         return os.path.join(os.path.dirname(root),d)
        return boost_directory_value


    return ''


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


print(sys.version,"is version of python")
if sys.version_info > (3, 6):
    with open("README.md", "r",encoding='utf-8') as fh:
        long_description = fh.read()
else:
        long_description =""


ext_modules = [
    Extension(
        'pydggrid',
        [os.path.join(dir_path, 'src', 'main.cpp')]
        + glob.glob(os.path.join(dir_path, 'src', 'lib', 'dggrid', '*.cpp'))
        + glob.glob(os.path.join(dir_path, 'src', 'lib', 'dglib', 'include', '*.cpp'))
        + glob.glob(os.path.join(dir_path, 'src', 'lib', 'shapelib', 'include', '*.c'))
        + glob.glob(os.path.join(dir_path, 'src', 'lib', 'proj4lib', 'include', '*.cpp'))
        + glob.glob(os.path.join(dir_path, 'src', 'lib', '*.cpp'))
        ,
        include_dirs=[
            # os.path.join('src','dggrid'),
            os.path.join(dir_path, 'src', 'lib', 'shapelib', 'include'),
            os.path.join(dir_path, 'src', 'lib', 'proj4lib', 'include'),
            # FIXME: install issue for venv
            '/usr/local/include/python3.6',
            # ,
            # 'E:/Personal/Lab/DGGRID/boost_1_70_0',
            # Path to pybind11 headers
            get_pybind_include(),
            get_boost_include(),
            get_pybind_include(user=True)
        ],
        library_dirs=[],
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
            # Add Wno-unknown-pragmas
            # pragma warning(suppress : 4996)
            opts.append('-Wno-unknown-pragmas')

            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
            opts.append('-D_hypot=hypot')
            opts.append('/w')
            opts.append('/Y-')
        for ext in self.extensions:
            ext.extra_compile_args = opts
        build_ext.build_extensions(self)


setup(
    name='pydggrid',
    version=__version__,
    author='Majid Hojati',
    author_email='asd56yu@gmail.com',
    url='https://github.com/am2222/pydggrid',
    description='Python wrapper for DGGRID',
    long_description=long_description,
    long_description_content_type="text/markdown",
    ext_modules=ext_modules,
    install_requires=['pybind11>=2.2'],
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
