import unittest
import pydggrid




def get_suite():
    "Return a unittest.TestSuite."
    import pydggrid.tests

    loader = unittest.TestLoader()
    suite = loader.loadTestsFromModule(pydggrid.tests)
    return suite
# def get_suite():
#     loader = unittest.TestLoader()
#     suite = loader.loadTestsFromModule(pydggrid)
#     return suite