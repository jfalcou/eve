#include <eve/eve.hpp>
#include <eve/module/combinatorial.hpp>
#include <iostream>

int main() {
   eve::wide n{93, 25, 32, 368,  216,  43, 18, 25};
   eve::wide p{42, 30, 27, 1024, 36, 12, 51, 44};
   std::cout << "<- n   = " << n   << "\n";
   std::cout << "<- p   = " << p   << "\n";

   auto [gcd, x, y] = eve::bezout(n, p);
   std::cout << "-> x                   = " << x << "\n";
   std::cout << "-> y                   = " << y << "\n";
   std::cout << "-> gcd(                = " << gcd << "\n";
   std::cout << "-> x*n+y*p             = " << x*n+y*p<< "\n";
}
