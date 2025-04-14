import unittest
from Boliche import computa_placar

class TestBoliche(unittest.TestCase):
    
    def test_simples(self):
        self.assertEqual(90, computa_placar("9-9-9-9-9-9-9-9-9-9-"))
        self.assertEqual(80, computa_placar("8-8-8-8-8-8-8-8-8-8-"))
        self.assertEqual(50, computa_placar("5-5-5-5-5-5-5-5-5-5-"))

    def test_completo(self):
        self.assertEqual(300, computa_placar("XXXXXXXXXXXX"))
        self.assertEqual(30, computa_placar("X--X--X----------------"))
        self.assertEqual(16, computa_placar("X12------------------"))
        self.assertEqual(300, computa_placar("XXXXXXXXXXXX"))
        self.assertEqual(90, computa_placar("9-9-9-9-9-9-9-9-9-9-"))
        self.assertEqual(0, computa_placar("--------------------"))
        self.assertEqual(167, computa_placar("X7/9-X-88/-6XXX81"))
    
    def test_caracteres_invalidos(self):
        self.assertEqual(0, computa_placar(""))
        self.assertEqual(0, computa_placar("ABC!@#"))
        self.assertEqual(5, computa_placar("5-----"))


if __name__ == '__main__':
    unittest.main()