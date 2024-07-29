// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0, -0.0, 1.0, -1.0, -0.5, 0.5, 0.75, -0.75};

  std::cout << "<- wf                         = " << wf << "\n";

  std::cout << "-> erf_inv(wf)                = " << eve::erf_inv(wf) << "\n";
  std::cout << "-> erf_inv[ignore_last(2)](wf)= " << eve::erf_inv[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> erf_inv[wf >= 0.0](wf)     = " << eve::erf_inv[wf >= 0.0](wf) << "\n";
}
