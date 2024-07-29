// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wu = {1u, 2u, 3u, 4u, 5u, 6u, 181u, 182u};

  std::cout << "<- wu = " << wu << "\n";

  std::cout << "-> double_factorial(wu)                = " << eve::double_factorial(wu) << "\n";
  std::cout << "-> double_factorial[ignore_last(2)](wu)= " << eve::double_factorial[eve::ignore_last(2)](wu) << "\n";
  std::cout << "-> double_factorial[wu != 182u](wu)    = " << eve::double_factorial[wu != 182u](wu) << "\n";
}
