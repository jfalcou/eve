// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
kumi::tuple wt{wf,2*wf,3*wf}; 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wt = " << wt << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> sub(wf, 2*wf)                = " << eve::sub(wf, 2*wf) << "\n";
   std::cout << "-> sub(wi, 2*wi)                = " << eve::sub(wi, 2*wi) << "\n";
   std::cout << "-> sub(wu, 2*wu)                = " << eve::sub(wu, 2*wu) << "\n";
   std::cout << "-> sub(wt)                      = " << eve::sub(wt) << "\n";
   std::cout << "-> sub[ignore_last(2)](wf, 2*wf)= " << eve::sub[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> sub[wf != 0](wf, 2*wf)       = " << eve::sub[wf != 0](wf, 2*wf) << "\n";
}
