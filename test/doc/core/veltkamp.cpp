// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf = {1.0, 0.1, 3.14159265358979, 1.0e10};

  std::cout << std::setprecision(20);
  std::cout << "<- wf            = " << wf << "\n";
  std::cout << "-> veltkamp(wf)  = " << eve::veltkamp(wf) << "\n";

  auto [xh, xl] = eve::veltkamp(wf);
  std::cout << "   xh            = " << xh << "\n";
  std::cout << "   xl            = " << xl << "\n";
  std::cout << "   xh + xl       = " << xh + xl << "\n";
}
