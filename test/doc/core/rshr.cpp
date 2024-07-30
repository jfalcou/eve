// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};

  std::cout << "<- wi0                            = " << wi0 << "\n";
  std::cout << "<- wi1                            = " << wi1 << "\n";
                                                  
  std::cout << "-> rshr(wi0, wi1)                 = " << eve::rshr(wi0, wi1) << "\n";
  std::cout << "-> rshr[ignore_last(2)](wi0, wi1) = " << eve::rshr[eve::ignore_last(2)](wi0, wi1) << "\n";
  std::cout << "-> rshr[wi0 != 0](wi0, wi1)       = " << eve::rshr[wi0 != 0](wi0, wi1) << "\n";
}
