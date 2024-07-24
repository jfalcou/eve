// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {1.0f, 2.0f, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> acosh(wf)                = " << eve::acosh(wf) << "\n";
  std::cout << "-> acosh[ignore_last(2)](wf)= " << eve::acosh[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acosh[wf != 2.0f](wf)    = " << eve::acosh[wf != 2.0f](wf) << "\n";
}
