// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 2.0f, -1.0f, -0.5f};
  
  std::cout << "<- wf                      = " << wf << "\n";
  
  std::cout << "-> acot(wf)                = " << eve::acot(wf) << "\n";
  std::cout << "-> acot[ignore_last(2)](wf)= " << eve::acot[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acot[wf != 2.0f](wf)    = " << eve::acot[wf != 2.0f](wf) << "\n";
}
