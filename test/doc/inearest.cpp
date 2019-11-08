#include <eve/function/inearest.hpp>
#include <eve/constant/bitincrement.hpp>
#include <eve/constant/eps.hpp>
#include <eve/wide.hpp>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 2.0f, eve::Eps<float>(), eve::Bitincrement<float>()};
  wide_it pi = {-1, 2, -3, -32};

  std::cout << "---- simd" << '\n'
            << "<- pf =                " << std::setprecision(12) << pf << '\n'
            << "-> eve::inearest(pf) =     " << eve::inearest(pf) << '\n'
            << "<- pi =                " << pi << '\n'
            << "-> eve::inearest(pi) =     " << eve::inearest(pi) << '\n';

  float        xf = 0.0f;
  std::int16_t xi = -3;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                " << xf << '\n'
            << "-> eve::inearest(xf) =     " << eve::inearest(xf) << '\n'
            << "<- xi =                " << xi << '\n'
            << "-> eve::inearest(xi) =     " << eve::inearest(xi) << '\n';
  return 0;
}
