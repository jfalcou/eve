// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.5f, -1.5f, -1.0f, 1.0f, 5.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                        = " << wf << "\n";

  std::cout << "-> tgamma(wf)                = " << eve::tgamma(wf) << "\n";
  std::cout << "-> tgamma[ignore_last(2)](wf)= " << eve::tgamma[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> tgamma[wf > 0.0f](wf)     = " << eve::tgamma[wf > 0.0f](wf) << "\n";
}
