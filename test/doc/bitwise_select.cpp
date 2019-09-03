#include <eve/function/bitwise.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/wide.hpp>
#include <iostream>

using iT      = std::uint32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;

int main()
{
  wide_it pi = {3, -2, -10, 0};
  wide_it qi = {4, -1, 0, 5};
  wide_it si = {2, eve::Allbits<iT>(), 0, 4};

  std::cout << "---- simd" << '\n'
            << " <- si =                              " << si << '\n'
            << " <- pi =                              " << pi << '\n'
            << " <- qi =                              " << qi << '\n'
            << " -> eve::bitwise_select(si, pi, qi) =  " << eve::bitwise_select(si, pi, qi) << '\n';

  iT ssi = 3, xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " ssi =                                " << ssi << '\n'
            << " xi =                                 " << xi << '\n'
            << " yi =                                 " << yi << '\n'
            << " -> eve::bitwise_select(ssi, xi, yi) = " << eve::bitwise_select(ssi, xi, yi)
            << '\n';
  return 0;
}
