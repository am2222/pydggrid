rmdir /Q /S  dist
python setup.py build --compiler=msvc
python setup.py sdist
python setup.py sdist bdist_wheel
python -m pip install dist/??
python -m twine upload dist/*