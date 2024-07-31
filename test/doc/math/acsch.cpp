// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {1.0f, 2.0f, eve::inf(eve::as<float>()), 0.5f};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> acsch(wf)                = " << eve::acsch(wf) << "\n";
  std::cout << "-> acsch[ignore_last(2)](wf)= " << eve::acsch[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acsch[wf != 2.0f](wf)    = " << eve::acsch[wf != 2.0f](wf) << "\n";
}
