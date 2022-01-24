//#include <eve/function/gcd.hpp>
#include <eve/module/combinatorial.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<int, eve::fixed<4>>;
  w_t pi = {93, 25, 32, 368}, qi = {42, 30, 27, 1024};

  std::cout << "---- simd" << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " -> gcd(pi, qi)     = " << eve::gcd(pi, qi) << '\n';

  std::uint32_t xi = 18, yi = 60;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> gcd(xi, yi)     = " << eve::gcd(xi, yi) << '\n';
  return 0;
}
