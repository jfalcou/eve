// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.125, 0.25, 0.375, 0.5, 0.625, 0.875, 1.0, 1.125};
  auto pi = eve::pi(eve::as(wf));
  wf *= pi;

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> cos(wf)                 = " << eve::cos(wf) << "\n\n";

  std::cout << "-> wf <= 0.25*pi           = " << (wf <= 0.25*pi)   << "\n";
  std::cout << "-> cos[quarter_circle](wf) = " << eve::cos[eve::quarter_circle](wf) << "\n\n";

  std::cout << "-> wf <= 0.5*pi            = " << (wf <= 0.5*pi)   << "\n";
  std::cout << "-> cos[half_circle](wf)    = " << eve::cos[eve::half_circle](wf) << "\n\n";

  std::cout << "-> wf <= pi                = " << (wf <= pi)   << "\n";
  std::cout << "-> cos[full_circle](wf)    = " << eve::cos[eve::full_circle](wf) << "\n\n";


}
