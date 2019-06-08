Build PyDGGRID From Source
============================
To Build PyDGGRID from source follow these steps:

Linux
-------------------------
- Install boost on linux

```
$ sudo apt install libboost-dev
$ sudo apt install libboost-all-dev
```

- Set `boost_dir` environment variable

After installing boost; set `boost_dir` variable in terminal/command prompt windows.

`expot boost_dir=/home/usr/include/boost/`

- clone this repository

- `pip install ./pydggrid`

 or you can easily call

- `python setup.py install`


Windows
-------------------------
.. note:: You need Build Tools for Visual Studio to be able to compile it from source. so Install it from this link `https://visualstudio.microsoft.com/downloads/`

- Install boost

Download latest version of boost from folowing link

`https://www.boost.org/users/download/`

then extract it in a folder. and it is done. After installing boost;

- Set `boost_dir` variable

`set "boost_dir=C:/Boost/include/"`

- clone this repository

- `pip install ./pydggrid`

 or you can easily call

- `python setup.py install`



