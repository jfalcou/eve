// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  using w_t =  eve::wide<double, eve::fixed<1>>;
  std::cout << eve::hurwitz(3.0, 15.0) << std::endl;
  std::cout << " ================================ "<< std::endl;
  std::cout << eve::hurwitz(3.0, w_t(15.0)) << std::endl;
}
