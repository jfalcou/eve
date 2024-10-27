// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wd = {0.0, -1.0, 8.0, 1.5, 2.0, 16.0, 15.3, 17.2};

  std::cout << "<- wd                      = " << wd << "\n";

  std::cout << "-> ilogb(wd)                = " << eve::ilogb(wd) << "\n";
  std::cout << "-> ilogb[ignore_last(2)](wd)= " << eve::ilogb[eve::ignore_last(2)](wd) << "\n";
  std::cout << "-> ilogb[wd != 2.0](wd)     = " << eve::ilogb[wd != 2.0](wd) << "\n";
}
