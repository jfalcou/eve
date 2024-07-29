// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf{0.5f, -1.5f, -1.0f, 1.0f, -2.5f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                         = " << wf << "\n";

  std::cout << "-> signgam(wf)                = " << eve::signgam(wf) << "\n";
  std::cout << "-> signgam[ignore_last(2)](wf)= " << eve::signgam[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> signgam[wf != -1.5f](wf)   = " << eve::signgam[wf != -1.5f](wf) << "\n";
}
