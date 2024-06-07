#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_logical_notand(auto a, auto b) { return eve::logical_notand(a, b); }

int main()
{
  using eve::is_even;
  using eve::is_odd;
  wide_ft pf = {3.0f, -2.0f, -3.0f, 51.04f};
  wide_ft qf = {4.0f, -1.0f, -3.0f, 0.0f};
  std::cout << "---- simd" << '\n'
            << " <- pf                                           = " << pf << '\n'
            << " <- qf                                           = " << qf << '\n'
            << " -> eve::logical_notand(is_odd(pf), is_even(qf)) = " << eve::logical_notand(is_odd(pf), is_even(qf)) << '\n';

  constexpr float xf = 3.0f, yf = 4.5f;

  std::cout << "---- scalar" << '\n'
            << " xf                                              = " << xf << '\n'
            << " yf                                              = " << yf << '\n'
            << " -> eve::logical_notand(is_odd(xf), is_even(yf)) = " << eve::logical_notand(is_odd(xf), is_even(yf)) << '\n'
            << " -> eve::logical_notand(xf == 3,    is_even(yf)) = " << eve::logical_notand(xf == 3   , is_even(yf)) << '\n' ;

  std::cout << "-> constexpr_logical_notand(xf > 1, yf < 2) = " << constexpr_logical_notand(xf > 1, yf < 2) << std::endl;

  return 0;
}
