#include <eve/eve.hpp>
#include <eve/module/combinatorial.hpp>
#include <iostream>

int main() {
   eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
   eve::wide n{0u, 6u, 6542u, 15u, 104729u, 104730u, 10000u, 1000u};

   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- n  = " << n << "\n";

   std::cout << "-> prime_ceil(wu)= " << eve::prime_ceil(wu) << "\n";
   std::cout << "-> prime_ceil(n) = " << eve::prime_ceil(n) << "\n";
   std::cout << "note 0 answer meaning 'out of implemented range'\n";
}
