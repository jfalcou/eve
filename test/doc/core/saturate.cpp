// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2)+32767;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2+32767;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i+32764;});

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n";

   std::cout << "-> saturate(wf, as(wu))= " << eve::saturate(wf, eve::as<std::int16_t>()) << "\n";
   std::cout << "-> saturate(wi, as(wu))= " << eve::saturate(wi, eve::as<std::int16_t>()) << "\n";
   std::cout << "-> saturate(wu, as(wi))= " << eve::saturate(wu, eve::as<std::int16_t>()) << "\n";
}
