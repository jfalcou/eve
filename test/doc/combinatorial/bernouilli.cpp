// revision 1
#include <eve/module/combinatorial.hpp>
#include <iostream>

eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
eve::wide n{90u, 25u, 32u, 180u, 8u, 10u, 12u, 14u};
int main(){
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- n  = " << n << "\n";

   std::cout << "-> bernouilli(wu)                = " << eve::bernouilli(wu) << "\n";
   std::cout << "-> bernouilli[ignore_last(2)](wu)= " << eve::bernouilli[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> bernouilli[wu != 2u](wu)      = " << eve::bernouilli[wu != 2u](wu) << "\n";
   std::cout << "-> bernouilli(n)                 = " << eve::bernouilli(n) << "\n";
}
