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
 
   std::cout << "-> manhattan(wf, 2*wf)                = " << eve::manhattan(wf, 2*wf) << "\n";
   std::cout << "-> manhattan(wi, 2*wi)                = " << eve::manhattan(wi, 2*wi) << "\n";
   std::cout << "-> manhattan(wu, 2*wu)                = " << eve::manhattan(wu, 2*wu) << "\n";
   std::cout << "-> manhattan(wt)                      = " << eve::manhattan(wt) << "\n";
   std::cout << "-> manhattan[ignore_last(2)](wf, 2*wf)= " << eve::manhattan[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> manhattan[wf != 0](wf, 2*wf)       = " << eve::manhattan[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> manhattan[pedantic](wf, 2*wf)      = " << eve::manhattan[eve::pedantic](wf, 2*wf) << "\n";
}
