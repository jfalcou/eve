// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i+c/2);});
  eve::wide bads{0.0, -0.0, -1.0, -2.5};
  std::cout << "<- wf   = " << wf << "\n";
  std::cout << "<- bads = " << bads << "\n";

  std::cout << "-> log_gamma(wf)                = " << eve::log_gamma(wf) << "\n";
  std::cout << "-> log_gamma[ignore_last(2)](wf)= " << eve::log_gamma[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> log_gamma[wf != 12.0f](wf)   = " << eve::log_gamma[wf != 12.0f](wf) << "\n";
  std::cout << "-> log_gamma(bads)              = " << eve::log_gamma(bads)<< "\n";
}
