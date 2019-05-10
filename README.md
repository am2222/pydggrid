PyDGGRID
==============

A wrapper for DGGRID in python
Installation
------------

**On Unix (Linux, OS X)**

 - clone this repository
 - `pip install ./pydggrid`
 
 or you can easily call
 
 - `python setup.py install`

**How To Use**
In order to use this library use following example. (more updates are comming on documentations section)
```
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
Building the documentation
--------------------------

Documentation for the project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

 - `cd pydggrid/docs`
 - `make html`

License
-------

By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.

Based on Kevin Sahr's DGGRID library (https://discreteglobalgrids.org).
Developed on top of the R package which was developed by Richard Barnes (https://github.com/r-barnes/dggridR/).

Test call
---------

```python
import pydggrid
```
