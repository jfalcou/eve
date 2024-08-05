// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};

  std::cout << "<- wi0                                = " << wi0 << "\n";
                                                      
  std::cout << "-> firstbitunset(wi0)                 = " << eve::firstbitunset(wi0) << "\n";
  std::cout << "-> firstbitunset[ignore_last(2)](wi0) = " << eve::firstbitunset[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> firstbitunset[wi0 != 0](wi0)       = " << eve::firstbitunset[wi0 != 0](wi0) << "\n";
}
