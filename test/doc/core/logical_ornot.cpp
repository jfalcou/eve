#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_logical_ornot(auto a, auto b) { return eve::logical_ornot(a, b); }

int main()
{
  using eve::is_even;
  using eve::is_odd;
  wide_ft pf = {3.0f, -2.0f, -3.0f, 51.04f};
  wide_ft qf = {4.0f, -1.0f, -3.0f, 0.0f};
  std::cout << "---- simd" << '\n'
            << " <- pf                                          = " << pf << '\n'
            << " <- qf                                          = " << qf << '\n'
            << " -> eve::logical_ornot(is_odd(pf), is_even(qf)) = " << eve::logical_ornot(is_odd(pf), is_even(qf)) << '\n';

  float xf = 3.0f, yf = 4.5f;

  std::cout << "---- scalar" << '\n'
            << " xf                                             = " << xf << '\n'
            << " yf                                             = " << yf << '\n'
            << " -> eve::logical_ornot(is_odd(xf), is_even(yf)) = " << eve::logical_ornot(is_odd(xf), is_even(yf)) << '\n'
            << " -> eve::logical_ornot(xf == 3,    is_even(yf)) = " << eve::logical_ornot(xf == 3   , is_even(yf)) << '\n' ;

  std::cout << "-> constexpr_logical_ornot(true, false) = " << constexpr_logical_ornot(true, false) << std::endl;

  return 0;
}
