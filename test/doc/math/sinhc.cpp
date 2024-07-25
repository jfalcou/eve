// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 1.5, 2.0, 20.25, -10.0, -2.0,
                  eve::inf(eve::as<double>()), eve::nan(eve::as<double>())};
  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> sinhc(wf)                = " << eve::sinhc(wf) << "\n";
  std::cout << "-> sinhc[ignore_last(2)](wf)= " << eve::sinhc[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sinhc[wf != -2.0f](wf)   = " << eve::sinhc[wf != -2.0f](wf) << "\n";
}
