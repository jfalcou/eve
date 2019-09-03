#include <eve/function/bitwise.hpp>
#include <eve/wide.hpp>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;

int main()
{
  wide_it pi = {100, 200, -2, 3};
  wide_it qi = {1, 2, 3, 2};

  std::cout << "---- simd" << '\n'
            << "<- pi =              " << pi << '\n'
            << "<- qi =              " << qi << '\n'
            << "-> eve::bitwise_shl(pi, qi) = " << eve::bitwise_shl(pi, qi) << '\n';

  iT xi = 2, mxi = -2, yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xi  =                      " << xi << '\n'
            << "<- mxi =                      " << mxi << '\n'
            << "<- yi  =                      " << yi << '\n'
            << "-> eve::bitwise_shl(xi, yi) = " << eve::bitwise_shl(xi, yi) << '\n'
            << "-> eve::bitwise_shl(mxi, yi)= " << eve::bitwise_shl(mxi, yi) << '\n';
  return 0;
}
