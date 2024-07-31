// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main()
{
  eve::wide wf = {0.0, 1.0, 2.0, -0.0, -1.0, -2.0,
                  eve::inf(eve::as<double>()), eve::nan(eve::as<double>())};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> coth(wf)                = " << eve::coth(wf) << "\n";
  std::cout << "-> coth[ignore_last(2)](wf)= " << eve::coth[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> coth[wf != -2.0f](wf)   = " << eve::coth[wf != -2.0f](wf) << "\n";
}
