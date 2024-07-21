// revision 1
#include <eve/module/combinatorial.hpp>
#include <iostream>

eve::wide<double> wf0([](auto i, auto c)->double{ return 2*(i-c/2);});
eve::wide<double> wf1([](auto i, auto c)->double{ return  2*(i+c/2);});
eve::wide<std::uint64_t> n([](auto i, auto )->std::uint64_t{ return 5*i;});

int main(){
   std::cout << "<- wf0 = " << wf0 << "\n";
   std::cout << "<- wf1 = " << wf1 << "\n";
   std::cout << "<- n   = " << n   << "\n";

   std::cout << "-> fibonacci(n, wf0, wf1)= " << eve::fibonacci(n, wf0, wf1) << "\n";
}
