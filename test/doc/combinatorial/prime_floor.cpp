// revision 1
#include <eve/module/combinatorial.hpp>
#include <iostream>

eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
eve::wide n{2u, 6u, 6542u, 15u, 1u, 200000u, 10000u, 1000u};

int main(){
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- n  = " << n << "\n";

   std::cout << "-> prime_floor(wu)= " << eve::prime_floor(wu) << "\n";
   std::cout << "-> prime_floor(n) = " << eve::prime_floor(n) << "\n";
   std::cout << "note 0 answer meaning 'out of implemented range'\n";
}
