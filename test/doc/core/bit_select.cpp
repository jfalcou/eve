// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
eve::wide<std::uint32_t> wl([](auto i, auto )->std::uint32_t{  return 1 << 2*i; });

int main(){
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- wl = " << wl << "\n";

   std::cout << "-> bit_select(wl, wi, 0)= " << eve::bit_select(wl, wi, -1) << "\n";
   std::cout << "-> bit_select(wl, wu, 0)= " << eve::bit_select(wl, wu, ~0u) << "\n";
}
