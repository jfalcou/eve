// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.4, 2.2, -0.0, -0.25, -0.4, -2.2};
  wf *= 180;

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> cotd(wf)                = " << eve::cotd(wf) << "\n";
  std::cout << "-> cotd[ignore_last(2)](wf)= " << eve::cotd[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> cotd[wf != -2.0f](wf)   = " << eve::cotd[wf != -2.0f](wf) << "\n";
  std::cout << "-> cotd[quarter_circle](wf)= " << eve::cotd[eve::quarter_circle](wf) << "\n";
  std::cout << "-> cotd[half_circle](wf)   = " << eve::cotd[eve::half_circle](wf) << "\n";
  std::cout << "-> cotd[full_circle](wf)   = " << eve::cotd[eve::full_circle](wf) << "\n";
}
