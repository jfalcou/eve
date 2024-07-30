// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};

  std::cout << "<- wi0                          = " << wi0 << "\n";
                                                
  std::cout << "-> is_pow2(wi0)                 = " << eve::is_pow2(wi0) << "\n";
  std::cout << "-> is_pow2[ignore_last(2)](wi0) = " << eve::is_pow2[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> is_pow2[wi0 != 0](wi0)       = " << eve::is_pow2[wi0 != 0](wi0) << "\n";
}
