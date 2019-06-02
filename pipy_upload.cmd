rmdir /Q /S  dist
python setup.py sdist
python setup.py sdist bdist_wheel
python -m twine upload dist/*