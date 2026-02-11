// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, -0.0f, 1.0f, -1.0f,
                   -0.5f, 0.5f, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> argpi(wf)                 = " << eve::argpi(wf) << "\n";
  std::cout << "-> argpi[pedantic](wf)       = " << eve::argpi[eve::pedantic](wf) << "\n";
  std::cout << "-> argpi[ignore_last(2)](wf) = " << eve::argpi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> argpi[wf != 0.5f](wf)     = " << eve::argpi[wf != 0.5f](wf) << "\n";
}
