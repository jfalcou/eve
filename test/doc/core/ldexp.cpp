// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, 1, 2, 3, 4, 5, 6, 7};

  std::cout << "<- wf0                      = " << wf0 << "\n";
  std::cout << "<- wi0                      = " << wi0 << "\n";
  std::cout << "<- wi1                      = " << wi1 << "\n";

  std::cout << "-> ldexp(wf0, wi0)                 = " << eve::ldexp(wf0, wi0) << "\n";
  std::cout << "-> ldexp[ignore_last(2)](wf0, wi0) = " << eve::ldexp[eve::ignore_last(2)](wf0, 2*wi0) << "\n";
  std::cout << "-> ldexp[wf0 != 0](wf0, wi0)       = " << eve::ldexp[wf0 != 0](wf0, wi0) << "\n";
  std::cout << "-> ldexp(wf0, wi1)                 = " << eve::ldexp(wf0, wi1) << "\n";
  std::cout << "-> ldexp[ignore_last(2)](wf0, wi1  = " << eve::ldexp[eve::ignore_last(2)](wf0, wi1) << "\n";
  std::cout << "-> ldexp[wi1 != 2](wf0, wi1)        = " << eve::ldexp[wi1 != 2](wf0, wi1) << "\n";
}
