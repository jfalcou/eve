#include <eve/function/fma.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_t = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_t oi = {2, -3, 0, 4};
  wide_t pi = {3, -2, -10, 0};
  wide_t qi = {4, -1, 0, 5};

  std::cout << "---- oimd" << '\n'
            << " <- oi =                 " << oi << '\n'
            << " <- pi =                 " << pi << '\n'
            << " <- qi =                 " << qi << '\n'
            << " -> fma(oi, pi, qi) =    " << eve::fma(oi, pi, qi) << '\n';

  float wi = 3, xi = 3, yi = 4;
  std::cout << "---- scalar" << '\n'
            << " wi =                    " << wi << '\n'
            << " xi =                    " << xi << '\n'
            << " yi =                    " << yi << '\n'
            << " -> fma(wi, xi, yi) =    " << eve::fma(wi, xi, yi) << '\n';
  return 0;
}
