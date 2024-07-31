// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25,
                  eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> sech(wf)                = " << eve::sech(wf) << "\n";
  std::cout << "-> sech[ignore_last(2)](wf)= " << eve::sech[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sech[wf > 0.0](wf)      = " << eve::sech[wf > 0.0](wf) << "\n";
}
