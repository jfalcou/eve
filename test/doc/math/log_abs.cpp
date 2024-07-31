// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
                  eve::inf(eve::as<float>()), -4.0f, eve::nan(eve::as<float>())};

  std::cout << "<- wf                         = " << wf << "\n";

  std::cout << "-> log_abs(wf)                = " << eve::log_abs(wf) << "\n";
  std::cout << "-> log_abs[ignore_last(2)](wf)= " << eve::log_abs[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> log_abs[wf != 2.0f](wf)    = " << eve::log_abs[wf != 2.0f](wf) << "\n";
}
