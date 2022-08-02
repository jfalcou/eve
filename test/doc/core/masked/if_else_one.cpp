#include <eve/wide.hpp>
#include <iostream>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;
using wide_lt = eve::as_logical_t<wide_it>;

int main()
{
  wide_it pi  = {3, -2, -10, 0};
  wide_it si  = {2, -3, 0, 4};
  wide_lt lsi = {true, false, false, true};

  std::cout << "---- simd" << '\n'
            << " <- si =                              " << si << '\n'
            << " <- lsi =                             " << lsi << '\n'
            << " <- pi =                              " << pi << '\n'
            << " -> eve::if_else(si, pi, eve::allbits) =         "
            << eve::if_else(si, pi, eve::allbits) << '\n'
            << " -> eve::if_else(lsi, pi, eve::allbits) =        "
            << eve::if_else(lsi, pi, eve::allbits) << '\n';

  iT               ssi = 3, xi = 3;
  eve::logical<iT> lssi = false;

  std::cout << "---- scalar" << '\n'
            << " ssi =                                " << ssi << '\n'
            << " lssi =                               " << lssi << '\n'
            << " xi =                                 " << xi << '\n'
            << " -> eve::if_else(ssi, xi, eve::allbits) =        "
            << eve::if_else(ssi, xi, eve::allbits) << '\n'
            << " -> eve::if_else(lssi, xi, eve::allbits) =       "
            << eve::if_else(lssi, xi, eve::allbits) << '\n';
  return 0;
}
