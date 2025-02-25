// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide<std::uint32_t, eve::fixed<8>> qi = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  float pf = 1.2345678901f;

   std::cout << std::setprecision(10);
   std::cout << "<- pf = " << pf << "\n";
   std::cout << "<- qi = " << qi << "\n";
   std::cout << std::setprecision(8);
   std::cout << "-> significants(pf, qi)= " << eve::significants(pf, qi) << "\n";
}
