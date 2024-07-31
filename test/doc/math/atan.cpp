// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -5.0f, 6.25f, 1.0f, -2.0f};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> atan(wf)                = " << eve::atan(wf) << "\n";
  std::cout << "-> atan[ignore_last(2)](wf)= " << eve::atan[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> atan[wf != -2.0f](wf)   = " << eve::atan[wf != -2.0f](wf) << "\n";
}
