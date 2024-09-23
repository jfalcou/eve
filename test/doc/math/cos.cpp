// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= eve::pi[eve::lower](eve::as(wf));

  std::cout << "<- wf                     = " << wf << "\n";

  std::cout << "-> cos(wf)                = " << eve::cos(wf) << "\n";
  std::cout << "-> cos[ignore_last(2)](wf)= " << eve::cos[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> cos[wf > 0.0](wf)      = " << eve::cos[wf > 0.0](wf) << "\n";
  std::cout << "-> cos[quarter_circle](wf)= " << eve::cos[eve::quarter_circle](wf) << "\n";
  std::cout << "-> cos[half_circle](wf)   = " << eve::cos[eve::half_circle](wf) << "\n";
  std::cout << "-> cos[full_circle](wf)   = " << eve::cos[eve::full_circle](wf) << "\n";
}
