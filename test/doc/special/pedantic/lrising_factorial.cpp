#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using w32_t = eve::wide<std::int32_t, eve::fixed<4>>;
  using wf_t = eve::wide<float, eve::fixed<4>>;
  w32_t n = {1, 2, -3, 7};
  wf_t x = {1.0f,  1.5f, 2.0f, 2.5f};

  std::cout << "---- simd" << std::setprecision(17) << '\n'
            << " <- n                                   = " << n << '\n'
            << " <- x                                   = " << x << '\n'
            << " -> pedantic(lrising_factorial(n, x))   = " << eve::pedantic(eve::lrising_factorial)(n, x) << '\n';
   return 0;
}
