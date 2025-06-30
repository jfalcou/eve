// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide<double, eve::fixed<4>> z{0.125, 15, -2.45, 1.0};

  for(int i=0; i < 5 ; ++i)
  {
    std::cout << eve::polygamma(i, z) << std::endl;
  }
}
