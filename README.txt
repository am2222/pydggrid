
[![Build Status](https://travis-ci.org/am2222/pydggrid.svg?branch=master)](https://travis-ci.org/am2222/pydggrid)  [![Documentation Status](https://readthedocs.org/projects/pydggrid/badge/?version=latest)](https://pydggrid.readthedocs.io/en/latest/?badge=latest)  [![Build status](https://ci.appveyor.com/api/projects/status/pldf8fuw9bd5mvsm?svg=true)](https://ci.appveyor.com/project/am2222/pydggrid)   [![PyPI version](https://badge.fury.io/py/pydggrid.svg)](https://badge.fury.io/py/pydggrid)

      
      
PyDGGRID
==============

A wrapper for DGGRID in python. Currently based on last DGGRID version (6.4) from Kevin Sahr.

<p align="center">
  <img src="https://github.com/am2222/pydggrid/blob/master/docs/L6kmP.jpg?raw=true" alt="SPyDGGRID"/>
</p>

Installation
------------

Note: this library needs 'Boost' library for compile. so make sure you have installed boost C++ library before installing.
The first thing many people want to know is, “how do I build Boost?” The good news is that often, there's nothing to build. 
To install boost follow folowing steps
- Install boost on linux
```
$ sudo apt install libboost-dev
$ sudo apt install libboost-all-dev
```

- Install boost on windows

Download latest version of boost from folowing link
`https://www.boost.org/users/download/`
then extract it in a folder. and it is done. After installing boost; set `boost_dir` variable in terminal/command prompt windows. 

Linux `expot boost_dir=/home/usr/include/boost/`

Windows `set "boost_dir=C:/Boost/include/"`

Then simply use pip to install this library

`pip install pydggrid`


Build From source
------------
**On Unix (Linux, OS X)**
 - install boost
 - set `boost_dir` environment variable
 - clone this repository
 - `pip install ./pydggrid`
 
 or you can easily call
 
 - `python setup.py install`
 
**On Windows**
 - You need Build Tools for Visual Studio to be able to compile it from source. so Install it from this link `https://visualstudio.microsoft.com/downloads/`
 - install boost
 - set `boost_dir` environment variable
 - clone this repository
 - `pip install ./pydggrid`
 
 or you can easily call
 
 - `python setup.py install`

**How To Use**
In order to use this library use following example. (more updates are comming on documentations section)
```python
#import librarry
import pydggrid as m
#Construct a dggs object
m.dgconstruct();
#getting Q2di index for a (lat,long) point
m.geo_to_q2di(50,50)
#[4, 71, 211]
#getting Q2dd index for a (lat,long) point
m.geo_to_q2dd(50,50)
#[4.0, -0.1427860170187444, 0.7514696738643607]
#getting ProjTri index for a (lat,long) point
m.geo_to_projtri(50,50)
#[3.0, 0.5793988192307712, 0.4993911549756102]`
```



TODO
--------------------------
- Supporting All DGGRID functions
- Adding Boost Geometry Support


Building the documentation
--------------------------

Documentation for the project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

 - `cd pydggrid/docs`
 - `make html`


Run tests
---------
To run all tests for the package call folowing command in package directory

```
python3 -m unittest discover
```

License
-------

By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.

Based on Kevin Sahr's DGGRID library (https://discreteglobalgrids.org).

Developed on top of the R package which was developed by Richard Barnes (https://github.com/r-barnes/dggridR/).