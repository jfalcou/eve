// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 1.0, 42.0, 1.0e-300, 1.0e300,
                   0.0, -1.0e-200, eve::smallestposval(eve::as<double>()), eve::valmax(eve::as<double>()) };

  std::cout << "<- wf             = " << wf << "\n";
  std::cout << "-> safe_scale(wf) = " << eve::safe_scale(wf) << "\n";
}
