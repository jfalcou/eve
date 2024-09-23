// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= eve::pi[eve::lower](eve::as(wf));

  std::cout << "<- wf                     = " << wf << "\n";

  std::cout << "-> sec(wf)                = " << eve::sec(wf) << "\n";
  std::cout << "-> sec[ignore_last(2)](wf)= " << eve::sec[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sec[wf > 0.0](wf)      = " << eve::sec[wf > 0.0](wf) << "\n";
  std::cout << "-> sec[quarter_circle](wf)= " << eve::sec[eve::quarter_circle](wf) << "\n";
  std::cout << "-> sec[half_circle](wf)   = " << eve::sec[eve::half_circle](wf) << "\n";
  std::cout << "-> sec[full_circle](wf)   = " << eve::sec[eve::full_circle](wf) << "\n";
}
