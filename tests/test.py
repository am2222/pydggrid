import pydggrid as m
import unittest
# import somepackage.tests



class Test(unittest.TestCase):
    # def test_version(self):
    #     self.assertEqual(m.__version__, '0.0.6')
    def test_dgg_cunstruct(self):
        m.dgconstruct()


def main():
    "Run all of the tests when run as a module with -m."
    suite = m.tests.get_suite()
    runner = Test.test_dgg_cunstruct()
    runner.run(suite)

if __name__ == '__main__':
    main()