#include <eve/function/bitwise.hpp>
#include <eve/literals.hpp>
#include <eve/wide.hpp>

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>; 
  w_t pi = {3, 2, 3, 3}, qi = {4, 1, 1, ~0};

  std::cout << "---- simd" << '\n'
            << " <- pi =                      " << pi << '\n'
            << " <- qi =                      " << qi << '\n'
            << " -> eve::bitwise_and(pi, qi) = " << eve::bitwise_and(pi, qi)
            << '\n';

  std::uint32_t xi = 3, yi = 5;
  
  std::cout << "---- scalar" << '\n'
            << " xi =                         " << xi << '\n'
            << " yi =                         " << yi << '\n'
            << " -> eve::bitwise_and(xi, yi) = " << eve::bitwise_and(xi, yi)
            << '\n';
  return 0; 
}
