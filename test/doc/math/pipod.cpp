// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {44.0, 45.0, 46.0, 90.0, 112.5, 157.5, 180.0, 202.5};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> cosd(wf)                 = " << eve::cosd(wf) << "\n\n";

  std::cout << "-> wf <= 45              = " << (wf <= 45)   << "\n";
  std::cout << "-> cosd[quarter_circle](wf) = " << eve::cosd[eve::quarter_circle](wf) << "\n\n";


  auto [fn, xr, dxr] = eve::detail::rem180(wf);
  std::cout << "fn" << fn << std::endl;
  std::cout << "xr" << xr << std::endl;

}
