// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> erfc(wf)                = " << eve::erfc(wf) << "\n";
  std::cout << "-> erfc[ignore_last(2)](wf)= " << eve::erfc[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> erfc[wf <= 2.0f](wf)    = " << eve::erfc[wf <= 2.0f](wf) << "\n";
}
