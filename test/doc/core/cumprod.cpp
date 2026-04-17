// revision 0
#include <eve/module/core.hpp>
#include <iostream>


int main()
{
  kumi::tuple t{1.0, 2.0, 3.0, 4.0};
  std::cout << t << std::endl;
  std::cout << eve::cumprod(t) << std::endl;
  std::cout << eve::cumprod(1.0, 2.0, 3.0, 4.0) << std::endl;
  std::cout << eve::cumprod(t) << std::endl;


};
