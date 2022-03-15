#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;
using wide_lt = eve::as_logical_t<wide_it>;

int main()
{
  wide_it pi  = {3, -2, -10, 0};
  wide_it qi  = {4, -1, 0, 5};
  wide_it si  = {2, -3, 0, 4};
  wide_lt lsi = {true, false, false, true};

  std::cout << "---- simd" << '\n'
            << " <- si =                              " << si << '\n'
            << " <- lsi =                             " << lsi << '\n'
            << " <- pi =                              " << pi << '\n'
            << " <- qi =                              " << qi << '\n'
            << " -> eve::add[si](pi, qi) =        " << eve::add[ si ](pi, qi) << '\n'
            << " -> eve::add[lsi](pi, qi) =       " << eve::add[ lsi ](pi, qi) << '\n';

  iT               ssi = 3, xi = 3, yi = 4;
  eve::logical<iT> lssi = false;

  std::cout << "---- scalar" << '\n'
            << " ssi =                                " << ssi << '\n'
            << " lssi =                               " << lssi << '\n'
            << " xi =                                 " << xi << '\n'
            << " yi =                                 " << yi << '\n'
            << " -> eve::add[ssi](xi, yi) =       " << eve::add[ ssi ](xi, yi) << '\n'
            << " -> eve::add[(lssi](xi, yi) =      " << eve::add[ lssi ](xi, yi) << '\n';
  return 0;
}
