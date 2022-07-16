#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, -32700, 32700}, qi = {4, 1, -100, 100};
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2.5, -32.7, 1327.43}, qf = {4.2, 1.5, -100.834, 10.02};

  std::cout << "---- simd" << '\n'
            << " <- pi          = " << pi << '\n'
            << " <- qi          = " << qi << '\n'
            <<  " -> saturated(add)(pi, qi) = " << eve::saturated(eve::add)(pi, qi) << '\n';

  std::int16_t a = -32700;
  std::int16_t b = -32767;
  std::int16_t c = 32767;
  std::cout << "---- scalar" << '\n'
            <<  " <- a                      = " << a << '\n'
            <<  " <- b                      = " << b << '\n'
            <<  " <- c                      = " << c << '\n'
            << " -> saturated(add)(a, b, c) = " << eve::saturated(eve::add)(a, b, c) << '\n'
            << " -> saturated(add)(c, b, a) = " << eve::saturated(eve::add)(c, b, a) << '\n';


            ;
  return 0;
}
