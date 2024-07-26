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
 
   std::cout << "-> oneminus(wf)                = " << eve::oneminus(wf) << "\n";
   std::cout << "-> oneminus(wi)                = " << eve::oneminus(wi) << "\n";
   std::cout << "-> oneminus(wu)                = " << eve::oneminus(wu) << "\n";
   std::cout << "-> oneminus[ignore_last(2)](wf)= " << eve::oneminus[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> oneminus[wf != 0](wf)       = " << eve::oneminus[wf != 0](wf) << "\n";
   std::cout << "-> oneminus[saturated ](wf)    = " << eve::oneminus[eve::saturated ](wf) << "\n";
}
