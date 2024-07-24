// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {1.0f, 0.0f, eve::pio_2(eve::as<float>()), eve::pio_4(eve::as<float>())};

  std::cout << "<- wf                     = " << wf << "\n";

  std::cout << "-> agd(wf)                = " << eve::agd(wf) << "\n";
  std::cout << "-> agd[ignore_last(2)](wf)= " << eve::agd[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> agd[wf != -2.0f](wf)   = " << eve::agd[wf != -2.0f](wf) << "\n";
}
