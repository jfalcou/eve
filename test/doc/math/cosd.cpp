// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= 180;

  std::cout << "<- wf                     = " << wf << "\n";

  std::cout << "-> cosd(wf)                = " << eve::cosd(wf) << "\n";
  std::cout << "-> cosd[ignore_last(2)](wf)= " << eve::cosd[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> cosd[wf > 0.0](wf)      = " << eve::cosd[wf > 0.0](wf) << "\n";
  std::cout << "-> cosd[quarter_circle](wf)= " << eve::cosd[eve::quarter_circle](wf) << "\n";
}
