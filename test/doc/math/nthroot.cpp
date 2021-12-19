//#include <eve/function/nthroot.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_nt = eve::wide<std::uint32_t, eve::fixed<8>>;
int main()
{
  wide_ft pf = {2.0f, 64.0f, 4.0f, 2.0f, 2.0f,
                eve::minf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_nt qn = {4, 3, 2, 1, 0,  4, 3, 2};

  std::cout << "---- simd" << '\n'<< std::setprecision(20)
            << "<- pf                   = " << pf << '\n'
            << "<- qn                   = " << qn << '\n'
            << "-> nthroot(pf, qn)      = " << eve::nthroot(pf, qn) << '\n'
            << "-> raw(nthroot)(pf, qn) = " << eve::raw(eve::nthroot)(pf, qn) << '\n';

  double xf = 64.0f;
  int n = 3;

  std::cout << "---- scalar" << '\n' << std::setprecision(20)
            << "<- xf                   = " << xf << '\n'
            << "<- n                    = " << n << '\n'
            << "-> nthroot(xf, n)       = " << eve::nthroot(xf, n) << '\n'
            << "-> raw(nthroot)(xf, n)  = " << eve::raw(eve::nthroot)(xf, n) << '\n';
  return 0;
}
