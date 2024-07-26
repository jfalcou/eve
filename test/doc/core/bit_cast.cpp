// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> bit_cast(wf, as(wu))= " << eve::bit_cast(wf, eve::as(wu)) << "\n";
   std::cout << "-> bit_cast(wi, as(wu))= " << eve::bit_cast(wi, eve::as(wu)) << "\n";
   std::cout << "-> bit_cast(wu, as(wi))= " << eve::bit_cast(wu, eve::as(wi)) << "\n";
}
