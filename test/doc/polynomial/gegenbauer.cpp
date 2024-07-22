// revision 1
#include <eve/module/polynomial.hpp>
#include <iostream>

eve::wide xd{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
eve::wide n{0, 1, 2, 3, 4, 5, 6, 7};
double l(-3.0/8.0);

int main()
{
   std::cout << "<- xd = " << xd << "\n";
   std::cout << "<- n  = " << n << "\n";
   std::cout << "<- l  = " << l << "\n";

   std::cout << "-> gegenbauer(n, l, xd)         = " << eve::gegenbauer(n, l, xd) << '\n';
   std::cout << "-> gegenbauer(3, l, xd)         = " << eve::gegenbauer(3, l, xd) << '\n';
   std::cout << "-> gegenbauer(n, l, 0.3)        = " << eve::gegenbauer(n, l, 0.3) << '\n';
}
