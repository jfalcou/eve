#include <eve/function/fibonacci.hpp>
#include <eve/wide.hpp>
#include <iomanip>
#include <iostream>

int main()
{
  using w32_t = eve::wide<std::uint16_t, eve::fixed<8>>;
  w32_t n = {13, 25, 32, 180, 1, 2, 3, 4};
  using wf32_t = eve::wide<float, eve::fixed<8>>;
  wf32_t a = {1, 2, 3, 4, 0.5, 0.33, -4.5, 0};
  wf32_t b = {2, 3, 4, 0.5, 0.33, -4.5, 0, 1};

  std::cout << "---- simd" << '\n'
            << " <- n                        = " << n << '\n'
            << " <- a                        = " << a << '\n'
            << " <- b                        = " << b << '\n'
            << " -> fibonacci(n, a, b)       = " << eve::fibonacci(n, a, b) << '\n'
            << " -> fibonacci(4u, a, b)      = " << eve::fibonacci(4u, a, b)<< '\n'
            << " -> fibonacci(n, 1.0f, 3.0f) = " << eve::fibonacci(n, 1.0f, 3.0f) << '\n'
            << " -> fibonacci(n, 1.0f, b)    = " << eve::fibonacci(n, 1.0f, b) << '\n';

  std::uint32_t ns = 10;
  float    as = 1;
  float    bs = 1;
  std::cout << "---- scalar" << '\n'
            << " ns                           = " << ns << '\n'
            << " as                           = " << as << '\n'
            << " bs                           = " << bs << '\n'
            << " -> fibonacci(ns, as, bs)     = " << eve::fibonacci(ns, as, bs) << '\n';


  return 0;
}
