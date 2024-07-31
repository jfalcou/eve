// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> acsc(wf)                = " << eve::acsc(wf) << "\n";
  std::cout << "-> acsc[ignore_last(2)](wf)= " << eve::acsc[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acsc[wf != 2.0f](wf)    = " << eve::acsc[wf != 2.0f](wf) << "\n";
}
