#include <eve/eve.hpp>
#include <eve/module/combinatorial.hpp>
#include <iostream>

int main() {
   eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
   eve::wide n{90u, 25u, 32u, 180u, 8u, 10u, 12u, 14u};

   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- n  = " << n << "\n";

   std::cout << "-> bernoulli(wu)                = " << eve::bernoulli(wu) << "\n";
   std::cout << "-> bernoulli[ignore_last(2)](wu)= " << eve::bernoulli[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> bernoulli[wu != 2u](wu)      = " << eve::bernoulli[wu != 2u](wu) << "\n";
   std::cout << "-> bernoulli(n)                 = " << eve::bernoulli(n) << "\n";
}
