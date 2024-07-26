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
 
   std::cout << "-> round(wf)                = " << eve::round(wf) << "\n";
   std::cout << "-> round(wi)                = " << eve::round(wi) << "\n";
   std::cout << "-> round(wu)                = " << eve::round(wu) << "\n";
   std::cout << "-> round[ignore_last(2)](wf)= " << eve::round[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> round[ignore_last(2)](wi)= " << eve::round[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> round[ignore_last(2)](wu)= " << eve::round[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> round[wf != 0](wf)       = " << eve::round[wf != 0](wf) << "\n";
   std::cout << "-> round[wi != 0](wi)       = " << eve::round[wi != 0](wi) << "\n";
   std::cout << "-> round[wu != 0](wu)       = " << eve::round[wu != 0](wu) << "\n";
   std::cout << "-> round[upward](wf)        = " << eve::round[eve::upward](wf) << "\n";
   std::cout << "-> round[downward](wf)      = " << eve::round[eve::downward](wf) << "\n";
   std::cout << "-> round[to_nearest](wf)    = " << eve::round[eve::to_nearest](wf) << "\n";
   std::cout << "-> round[toward_zero](wf)   = " << eve::round[eve::toward_zero](wf) << "\n";
}
