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
    << " -> pedantic(fanm)(pf, qf, rf) = " << eve::pedantic(eve::fanm)(pf, qf, rf) << '\n'
    << " -> numeric(fanm)(pf, qf, rf)  = " << eve::numeric(eve::fanm)(pf, qf, rf) << '\n'
    << " -> fanm(pf, qf, rf)           = " << eve::fanm(pf, qf, rf) << '\n'
    << "\n if the last fanm result ends by '0, inf}', it is because\n"
    << " the system has no simd fanm fanmily intrinsics\n"
    << " or is not configured to use them.\n\n";


  float xf = 0.5f;
  float yf = 0.5f;
  float zf = 0.1f;
  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                         = " << xf << '\n'
    << "<- yf                         = " << yf << '\n'
    << "<- zf                         = " << yf << '\n'
    << "-> fanm(xf, yf, zf)           = " << eve::fanm(xf, yf, zf) << '\n';
  return 0;
}
