// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.5f, -1.5f, -1.0f, 1.0f, 5.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                                = " << wf << "\n";

  std::cout << "-> log_abs_gamma(wf)                 = " << eve::log_abs_gamma(wf) << "\n";
  std::cout << "-> log_abs_gamma[ignore_last(2)](wf) = " << eve::log_abs_gamma[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> log_abs_gamma[wf != 2.0f](wf)     = " << eve::log_abs_gamma[wf != 2.0f](wf) << "\n";
}
