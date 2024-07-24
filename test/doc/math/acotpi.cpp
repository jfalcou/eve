// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout << "<- wf                        = " << wf << "\n";

  std::cout << "-> acotpi(wf)                = " << eve::acotpi(wf) << "\n";
  std::cout << "-> acotpi[ignore_last(2)](wf)= " << eve::acotpi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acotpi[wf != 2.0f](wf)    = " << eve::acotpi[wf != 2.0f](wf) << "\n";
}
