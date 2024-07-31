// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> atanh(wf)                = " << eve::atanh(wf) << "\n";
  std::cout << "-> atanh[ignore_last(2)](wf)= " << eve::atanh[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> atanh[wf != -1.0f](wf)   = " << eve::atanh[wf != -1.0f](wf) << "\n";
}
