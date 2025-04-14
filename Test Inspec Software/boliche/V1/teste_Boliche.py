import unittest
from Boliche import computa_placar

class TestBoliche(unittest.TestCase):
    
    def test_simples(self):
        self.assertEqual(90, computa_placar("9-9-9-9-9-9-9-9-9-9-"))
        self.assertEqual(80, computa_placar("8-8-8-8-8-8-8-8-8-8-"))
        self.assertEqual(50, computa_placar("5-5-5-5-5-5-5-5-5-5-"))

if __name__ == '__main__':
    unittest.main()