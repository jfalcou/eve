// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};

  std::cout << "<- wi0                              = " << wi0 << "\n";
                                                    
  std::cout << "-> firstbitset(wi0)                 = " << eve::firstbitset(wi0) << "\n";
  std::cout << "-> firstbitset[ignore_last(2)](wi0) = " << eve::firstbitset[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> firstbitset[wi0 != 0](wi0)       = " << eve::firstbitset[wi0 != 0](wi0) << "\n";
}
