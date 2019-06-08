rmdir /Q /S  dist
set "boost_dir=E:/Personal/Lab/DGGRID/boost_1_70_0"
python setup.py build --compiler=msvc
python setup.py sdist
python setup.py sdist bdist_wheel
python -m twine upload dist/*