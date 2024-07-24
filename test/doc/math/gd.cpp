// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};

  std::cout << "<- wf                    = " << wf << "\n";

  std::cout << "-> gd(wf)                = " << eve::gd(wf) << "\n";
  std::cout << "-> gd[ignore_last(2)](wf)= " << eve::gd[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> gd[wf != -2.0](wf)    = " << eve::gd[wf != -2.0](wf) << "\n";
}
