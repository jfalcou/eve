// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -4.0f, -6.0f, 1.0f, -2.0f};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> asinh(wf)                = " << eve::asinh(wf) << "\n";
  std::cout << "-> asinh[ignore_last(2)](wf)= " << eve::asinh[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> asinh[wf != -2.0f](wf)   = " << eve::asinh[wf != -2.0f](wf) << "\n";
}
