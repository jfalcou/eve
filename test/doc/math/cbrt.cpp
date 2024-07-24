// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, 1.0f, -1.0f, -2.0f, 8.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> cbrt(wf)                = " << eve::cbrt(wf) << "\n";
  std::cout << "-> cbrt[ignore_last(2)](wf)= " << eve::cbrt[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> cbrt[wf != -2.0f](wf)   = " << eve::cbrt[wf != -2.0f](wf) << "\n";
}
