#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), 180.0f};

  auto [s, c]    = eve::sindcosd(pf);
  auto [ds, dc]  = eve::diff(eve::sindcosd)(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> sindcosd(pf)        = [" << '\n'
            << "                        " << s << ", \n"
            << "                        " << c << '\n'
            << "                       ]\n"
            << "-> diff(sindcosd)(pf)  = [" << '\n'
            << "                        " << ds << ", \n"
            << "                        " << dc << '\n'
            << "                       ]\n";

  float xf = 2.3;
  auto [ss, sc] =  eve::sindcosd(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf           =  " << xf << '\n'
            << "-> sindcosd(xf) = [" << ss << ", " << sc << "]\n";
  return 0;
}
