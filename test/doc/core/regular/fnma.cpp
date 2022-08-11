#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};
  wide_ft qf = { 1.0f, -1.0f, -0.5f, 0.0f};
  wide_ft rf = { 1.0f, 2.0f, -5.0f, 0.1f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                          = " << pf << '\n'
    << "<- qf                          = " << qf << '\n'
    << "<- rf                          = " << rf << '\n'
    << " -> pedantic(fnma)(pf, qf, rf) = " << eve::pedantic(eve::fnma)(pf, qf, rf) << '\n'
    << " -> numeric(fnma)(pf, qf, rf)  = " << eve::numeric(eve::fnma)(pf, qf, rf) << '\n'
    << " -> fnma(pf, qf, rf)           = " << eve::fnma(pf, qf, rf) << '\n'
    << "\n if the last fnma result ends by '0, inf}', it is because\n"
    << " the system has no simd fnma fnmaily intrinsics\n"
    << " or is not configured to use them.\n\n";


  float xf = 0.5f;
  float yf = 0.5f;
  float zf = 0.1f;
  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                         = " << xf << '\n'
    << "<- yf                         = " << yf << '\n'
    << "<- zf                         = " << yf << '\n'
    << "-> fnma(xf, yf, zf)           = " << eve::fnma(xf, yf, zf) << '\n';
  return 0;
}
