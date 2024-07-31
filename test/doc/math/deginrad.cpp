// revision 1
#include <eve/module/math.hpp>
#include <iostream>


int main()
{
  eve::wide wf{0.0, 200.0, 40.0, -17.0};

  std::cout << "<- wf                          = " << wf << "\n";

  std::cout << "-> deginrad(wf)                = " << eve::deginrad(wf) << "\n";
  std::cout << "-> deginrad[ignore_last(2)](wf)= " << eve::deginrad[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> deginrad[wf > 0.0](wf)      = " << eve::deginrad[wf > 0.0](wf) << "\n";
}
