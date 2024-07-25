// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.23, 0.3, 2.0, -0.0, -0.23, -0.3, -2.0};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> cscpi(wf)                = " << eve::cscpi(wf) << "\n";
  std::cout << "-> cscpi[ignore_last(2)](wf)= " << eve::cscpi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> cscpi[wf != -2.0f](wf)   = " << eve::cscpi[wf != -2.0f](wf) << "\n";
  std::cout << "-> cscpi[quarter_circle](wf)= " << eve::cscpi[eve::quarter_circle](wf) << "\n";
}
