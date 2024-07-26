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
 
   std::cout << "-> nearest(wf)                = " << eve::nearest(wf) << "\n";
   std::cout << "-> nearest(wi)                = " << eve::nearest(wi) << "\n";
   std::cout << "-> nearest(wu)                = " << eve::nearest(wu) << "\n";
   std::cout << "-> nearest[ignore_last(2)](wf)= " << eve::nearest[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> nearest[ignore_last(2)](wi)= " << eve::nearest[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> nearest[ignore_last(2)](wu)= " << eve::nearest[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> nearest[wf != 0](wf)       = " << eve::nearest[wf != 0](wf) << "\n";
   std::cout << "-> nearest[wi != 0](wi)       = " << eve::nearest[wi != 0](wi) << "\n";
   std::cout << "-> nearest[wu != 0](wu)       = " << eve::nearest[wu != 0](wu) << "\n";
}
