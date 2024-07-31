// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25,
                  eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> csch(wf)                = " << eve::csch(wf) << "\n";
  std::cout << "-> csch[ignore_last(2)](wf)= " << eve::csch[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> csch[wf > 0.0](wf)      = " << eve::csch[wf > 0.0](wf) << "\n";
}
