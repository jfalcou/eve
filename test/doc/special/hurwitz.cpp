// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide<double, eve::fixed<4>> z{0.125, 15, -2.45, 1.0};

  for(int i=2; i < 5 ; ++i)
  {
    std::cout << eve::hurwitz(i, z) << std::endl;
  }
//   using w_t =  eve::wide<double, eve::fixed<1>>;
//   std::cout << eve::hurwitz(3.0, 15.0) << std::endl;
//   std::cout << " ================================ "<< std::endl;
//   std::cout << eve::hurwitz(3.0, w_t(15.0)) << std::endl;
}
