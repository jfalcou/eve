// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide qi = {0, 1, 2, 3, 4, 5, 6, 7};
  float pf = 1.2345678901f;

   std::cout << std::setprecision(10);
   std::cout << "<- pf = " << pf << "\n";
   std::cout << "<- qi = " << qi << "\n";

   std::cout << "-> significants(pf, qi)= " << eve::significants(pf, qi) << "\n";
}
