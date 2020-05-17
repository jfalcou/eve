#include <eve/function/sinhcosh.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::Mindenormal<double>(),
               eve::Inf<double>(), eve::Minf<double>(), eve::Nan<double>()};

  auto [s, c]    = eve::sinhcosh(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> sinhcosh(pf)            = [" << '\n'
            << "                           " << s << ", \n"
            << "                           " << c << '\n'
            << "                             ]\n";

  float xf = 2.3;
  auto [ss, sc] =  eve::sinhcosh(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf           =  " << xf << '\n'
            << "-> sinhcosh(xf) = [" << ss << ", " << sc << "]\n";
  return 0;
}
