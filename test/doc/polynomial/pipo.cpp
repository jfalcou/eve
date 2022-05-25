#include <eve/module/core.hpp>
#include <iostream>

using value_type = float;
using w_t =  eve::wide<value_type>;


int main()
{
  auto zz =  value_type(1);
  auto x  =  value_type(2);
  w_t xx([&zz, x](auto ,  auto){ auto z = zz; zz *= x; return z;});

  std::cout << xx << std::endl;
  return 0;
}
