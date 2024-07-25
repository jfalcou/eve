// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.125, 0.25, 0.375, 0.5, 0.625, 0.875, 1.0, 1.125};
  auto pi = 180;
  wf *= pi;

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> cosd(wf)                 = " << eve::cosd(wf) << "\n\n";

  std::cout << "-> wf <= 0.25*pi           = " << (wf <= 0.25*pi)   << "\n";
  std::cout << "-> cosd[quarter_circle](wf) = " << eve::cosd[eve::quarter_circle](wf) << "\n\n";

  std::cout << "-> wf <= 0.5*pi            = " << (wf <= 0.5*pi)   << "\n";
  std::cout << "-> cosd[half_circle](wf)    = " << eve::cosd[eve::half_circle](wf) << "\n\n";

  std::cout << "-> wf <= pi                = " << (wf <= pi)   << "\n";
  std::cout << "-> cosd[full_circle](wf)    = " << eve::cosd[eve::full_circle](wf) << "\n\n";


}
