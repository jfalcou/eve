// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i+c/2);});

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> log_gamma(wf)                = " << eve::log_gamma(wf) << "\n";
  std::cout << "-> log_gamma[ignore_last(2)](wf)= " << eve::log_gamma[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> log_gamma[wf != -2.0f](wf)   = " << eve::log_gamma[wf != -2.0f](wf) << "\n";
}
