#include <eve/function/convert.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<double, eve::fixed<4>>;
using wide_it = eve::wide<std::int64_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.3f, 45000.7f, -64768.6f};
  wide_it pi = {-1, 2, -3, eve::Valmax<std::int64_t>()};

  std::cout << "---- simd" << '\n'
            << "<- pf =                                                         " << pf << '\n'
            << "-> eve::convert(pf, eve::as<std::int64_t>()) =                  " << eve::convert(pf, eve::as<std::int64_t>()) << '\n'
            << "-> eve::saturated_(eve::convert)(pf, eve::as<std::int16_t>()) = " << eve::saturated_(eve::convert)(pf, eve::as<std::int16_t>()) << '\n'
            << "-> eve::convert(pf, eve::as<std::int16_t>()) =                  " << eve::convert(pf, eve::as<std::int16_t>()) << '\n'    
            << "<- pi =                                                         " << pi << '\n'
            << "-> eve::convert(pi, eve::as<double>()) =                        " << eve::convert(pi, eve::as<double>()) << '\n'; 

  double        xf = -64768.4f;
  std::int64_t xi = -64768;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                                         " << xf << '\n'
            << "-> eve::convert(xf, eve::as<std::int64_t>()) =  " << eve::convert(xf, eve::as<std::int64_t>()) << '\n'
            << "<- xi =                                         " << xi << '\n'
            << "-> eve::eve::convert(xi, eve::as<double>()) =    " << eve::convert(xi, eve::as<double>()) << '\n';
  return 0;
}
