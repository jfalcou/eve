// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= 180;

  std::cout << "<- wf                     = " << wf << "\n";

  std::cout << "-> secd(wf)                = " << eve::secd(wf) << "\n";
  std::cout << "-> secd[ignore_last(2)](wf)= " << eve::secd[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> secd[wf > 0.0](wf)      = " << eve::secd[wf > 0.0](wf) << "\n";
  std::cout << "-> secd[quarter_circle](wf)= " << eve::secd[eve::quarter_circle](wf) << "\n";
}
