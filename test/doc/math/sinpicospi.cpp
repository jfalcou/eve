#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<4>>;

int main(){
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), 0.5f};

  auto [s, c]    = eve::sinpicospi(pf);
  auto [ds, dc]  = eve::diff(eve::sinpicospi)(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> sinpicospi(pf)       = [" << '\n'
            << "                        " << s << ", \n"
            << "                        " << c << '\n'
            << "                       ]\n"
            << "-> diff(sinpicospi)(pf) = [" << '\n'
            << "                        " << ds << ", \n"
            << "                        " << dc << '\n'
            << "                       ]\n";

  float xf = 2.3;
  auto [ss, sc] =  eve::sinpicospi(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf             =  " << xf << '\n'
            << "-> sinpicospi(xf) = [" << ss << ", " << sc << "]\n";
  return 0;
}
