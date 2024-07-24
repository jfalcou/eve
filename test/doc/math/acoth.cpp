// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {1.0f, 2.0f, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> acoth(wf)                = " << eve::acoth(wf) << "\n";
  std::cout << "-> acoth[ignore_last(2)](wf)= " << eve::acoth[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acoth[wf != 2.0f](wf)    = " << eve::acoth[wf != 2.0f](wf) << "\n";
}
