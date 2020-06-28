#include <eve/function/ifrexp.hpp>
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

  auto [m, e]    = eve::ifrexp(pf);
  auto [mp, ep]  = eve::pedantic_(eve::ifrexp)(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                    = " << pf << '\n'
            << "-> ifrexp(pf)            = [" << '\n'
            << "                           " << m << ", \n"
            << "                           " << e << '\n'
            << "                           ]\n"
            << "-> pedantic_(ifrexp)(pf) = [" << '\n'
            << "                           " << mp << ", \n"
            << "                           " << ep << '\n'
            << "                           ]\n";

  float xf = 2.3;
  auto [sm, se] =  eve::ifrexp(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf         =  " << xf << '\n'
            << "-> ifrexp(xf) = [" << sm << ", " << se << "]\n";
  return 0;
}
