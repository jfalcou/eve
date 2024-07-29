// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf{-10.0, -2.0, -0.5, 0.0, 0.2, 0.5, 10.0, 100.0};

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> omega(wf)                = " << eve::omega(wf) << "\n";
  std::cout << "-> omega[ignore_last(2)](wf)= " << eve::omega[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> omega[wf != -2.0f](wf)   = " << eve::omega[wf != -2.0f](wf) << "\n";
}
