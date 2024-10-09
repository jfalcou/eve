// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide<float> wf = [](auto i, auto c) { return 2.f*(i-c/2);};

  std::cout << "<- wf                    = " << wf << "\n";

  std::cout << "-> gd(wf)                = " << eve::gd(wf) << "\n";
  std::cout << "-> gd[ignore_last(2)](wf)= " << eve::gd[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> gd[wf != -2.0](wf)    = " << eve::gd[wf != -2.0](wf) << "\n";
}
