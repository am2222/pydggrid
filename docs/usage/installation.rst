PyDGGRID Installation
============================

.. note:: this library needs 'Boost' library for compile. so make sure you have installed boost C++ library before installing. The first thing many people want to know is, “how do I build Boost?” The good news is that often, there's nothing to build. To install boost follow these steps.

Install on Linux
-------------------------
- Install boost on linux

```
$ sudo apt install libboost-dev
$ sudo apt install libboost-all-dev
```

- Set `boost_dir` environment variable

After installing boost; set `boost_dir` variable in terminal/command prompt windows.

`expot boost_dir=/home/usr/include/boost/`

- Install PyDGGRID from pip

Then simply use pip to install this library

`pip install pydggrid`


Install on Windows
-------------------------

- Install boost

Download latest version of boost from folowing link

`https://www.boost.org/users/download/`

then extract it in a folder. and it is done. After installing boost;

- Set `boost_dir` variable

`set "boost_dir=C:/Boost/include/"`

Then simply use pip to install this library

`pip install pydggrid`


