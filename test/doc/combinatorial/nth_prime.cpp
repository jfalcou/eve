// revision 1
#include <eve/module/combinatorial.hpp>
#include <iostream>

eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
eve::wide n{52u, 53u, 6541u, 6542u, 0u, 1u, 999u, 10000u};

int main(){
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- n  = " << n  << "\n";

   std::cout << "-> nth_prime(wu)= " << eve::nth_prime(wu) << "\n";
   std::cout << "-> nth_prime(n) = " << eve::nth_prime(n) << "\n";
}
