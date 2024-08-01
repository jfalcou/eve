// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> secpi(wf)                = " << eve::secpi(wf) << "\n";
  std::cout << "-> secpi[ignore_last(2)](wf)= " << eve::secpi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> secpi[wf > 0.0](wf)      = " << eve::secpi[wf > 0.0](wf) << "\n";
  std::cout << "-> secpi[quarter_circle](wf)= " << eve::secpi[eve::quarter_circle](wf) << "\n";
}
