// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.4, 2.2, -0.0, -0.25, -0.4, -2.2};
  wf *= eve::pi[eve::downward](eve::as(wf));

  std::cout << "<- wf                     = " << wf << "\n";

  std::cout << "-> cot(wf)                = " << eve::cot(wf) << "\n";
  std::cout << "-> cot[ignore_last(2)](wf)= " << eve::cot[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> cot[wf > 0.0](wf)      = " << eve::cot[wf > 0.0](wf) << "\n";
  std::cout << "-> cot[quarter_circle](wf)= " << eve::cot[eve::quarter_circle](wf) << "\n";
  std::cout << "-> cot[half_circle](wf)   = " << eve::cot[eve::half_circle](wf) << "\n";
  std::cout << "-> cot[full_circle](wf)   = " << eve::cot[eve::full_circle](wf) << "\n";
}
