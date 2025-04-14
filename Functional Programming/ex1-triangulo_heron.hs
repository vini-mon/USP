-- Triangulo de Haron
-- s = semi-perimetro == (a+b+c)/2 
-- area = sqrt( s (s-a) (s-b) (s-c) )

main :: IO ()
main = do
    a <- readLn :: IO Int
    b <- readLn :: IO Int
    c <- readLn :: IO Int
    case ehTriangulo a b c of
        True -> putStrLn $ show $ heron (fromIntegral a) (fromIntegral b) (fromIntegral c)
        False -> putStrLn "-"
        
ehTriangulo :: Int -> Int -> Int -> Bool
ehTriangulo a b c
    | a <= 0 || b <= 0 || c <= 0 = False
    -- | a + b > c && a + c > b && b + c > a = True
    | a + b >= c && a + c >= b && b + c >= a = True
    | otherwise = False


heron :: Double -> Double -> Double -> Double
heron a b c = sqrt (s * (s - a) * (s - b) * (s - c))
  where s = (a + b + c) / 2
