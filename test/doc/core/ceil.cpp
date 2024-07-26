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
 
   std::cout << "-> ceil(wf)                = " << eve::ceil(wf) << "\n";
   std::cout << "-> ceil(wi)                = " << eve::ceil(wi) << "\n";
   std::cout << "-> ceil(wu)                = " << eve::ceil(wu) << "\n";
   std::cout << "-> ceil[ignore_last(2)](wf)= " << eve::ceil[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> ceil[ignore_last(2)](wi)= " << eve::ceil[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> ceil[ignore_last(2)](wu)= " << eve::ceil[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> ceil[wf != 0](wf)       = " << eve::ceil[wf != 0](wf) << "\n";
   std::cout << "-> ceil[wi != 0](wi)       = " << eve::ceil[wi != 0](wi) << "\n";
   std::cout << "-> ceil[wu != 0](wu)       = " << eve::ceil[wu != 0](wu) << "\n";
   std::cout << "-> ceil[almost](wf)        = " << eve::ceil[eve::almost](wf) << "\n";
}
