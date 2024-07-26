// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> bit_ceil(wf)                = " << eve::bit_ceil(wf) << "\n";
   std::cout << "-> bit_ceil(wi)                = " << eve::bit_ceil(wi) << "\n";
   std::cout << "-> bit_ceil(wu)                = " << eve::bit_ceil(wu) << "\n";
   std::cout << "-> bit_ceil[ignore_last(2)](wf)= " << eve::bit_ceil[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> bit_ceil[ignore_last(2)](wi)= " << eve::bit_ceil[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> bit_ceil[ignore_last(2)](wu)= " << eve::bit_ceil[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> bit_ceil[wf != 0](wf)       = " << eve::bit_ceil[wf != 0](wf) << "\n";
   std::cout << "-> bit_ceil[wi != 0](wi)       = " << eve::bit_ceil[wi != 0](wi) << "\n";
   std::cout << "-> bit_ceil[wu != 0](wu)       = " << eve::bit_ceil[wu != 0](wu) << "\n";
}
