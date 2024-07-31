// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 1.0, 2.0, 20.0, 100.0, 1000.0,
                  eve::inf(eve::as<double>()), eve::nan(eve::as<double>())};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> sinc(wf)                = " << eve::sinc(wf) << "\n";
  std::cout << "-> sinc[ignore_last(2)](wf)= " << eve::sinc[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sinc[wf != 2.0f](wf)    = " << eve::sinc[wf != 2.0f](wf) << "\n";
}
