// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return eve::is_odd(i) ? i-c/2 :c/2-i;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n";
   auto myless = [](auto x, auto y){return x > y; };

   std::cout << "-> sort(wf)         = " << eve::sort(wf) << "\n";
   std::cout << "-> sort(wi)         = " << eve::sort(wi) << "\n";
   std::cout << "-> sort(wu)         = " << eve::sort(wu) << "\n";
   std::cout << "-> sort(wf, myless) = " << eve::sort(wf, myless)  << "\n";
   std::cout << "-> sort(wi, myless) = " << eve::sort(wi, myless)  << "\n";
   std::cout << "-> sort(wu, myless) = " << eve::sort(wu, myless)  << "\n";
}
