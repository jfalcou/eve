// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::eps(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> log1p(wf)                = " << eve::log1p(wf) << "\n";
  std::cout << "-> log1p[ignore_last(2)](wf)= " << eve::log1p[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> log1p[wf != 2.0f](wf)    = " << eve::log1p[wf != 2.0f](wf) << "\n";
}
