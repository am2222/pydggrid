Build PyDGGRID From Source
============================
To Build PyDGGRID from source follow these steps:

Installation
------------

Note: The main `DGGRID` library needs 'GDAL' library to compile. so make sure you have installed GDAL C++ library before installing. To installing GDAL on linux is pretty straightforward. For windows you can use `vcpkg` to compile and install it. The process of installing and using `vcpkg` on windows can be found on its github (https://github.com/microsoft/vcpkg/)

- Install GDAL on linux
```
sudo add-apt-repository ppa:ubuntugis/ppa && sudo apt-get update
sudo apt-get update
sudo apt-get install gdal-bin
sudo apt-get install libgdal-dev
```

- Install GDAL on windows

Prerequisites:
```
Windows 10, 8.1, 7, Linux, or MacOS
Visual Studio 2015 Update 3 or newer (on Windows)
Git
```
To get started:
```
> git clone https://github.com/Microsoft/vcpkg.git
> cd vcpkg

PS> .\bootstrap-vcpkg.bat
```
then

```
PS> .\vcpkg integrate install
```
Install GDAL packages with
```
PS> .\vcpkg install gdal:x64-windows shapelib::x64-windows
```
NOTE: The GDAL version **must** match with your python compiled version. So if you have a x86 python use `vcpkg install gdal:x86-windows`, othewise use `vcpkg install gdal:x64-windows`

Then simply use pip to install this library

`pip install pydggrid`


Build From source
------------
**On Unix (Linux, OS X)**
 - install GDAL, shapelib
 - clone this repository
 - `pip install ./pydggrid`
 
 or you can easily call
 
 - `python setup.py install`
 
**On Windows**
 - You need Build Tools for Visual Studio to be able to compile it from source. so Install it from this link `https://visualstudio.microsoft.com/downloads/`
 - install GDAL, shapelib
 - clone this repository
 - `pip install ./pydggrid`
 
 or you can easily call
 
 - `python setup.py install`



