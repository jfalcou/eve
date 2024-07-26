// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i+1;});
kumi::tuple wt{8*wf,2*wf,4*wf};

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wt = " << wt << "\n";
   std::cout << "<- wu = " << wu << "\n";

   auto nz = [](auto wi){return eve::if_else(wi, wi, eve::one); };
   std::cout << "-> div(3*wf, 2*wf)              = " << eve::div(3*wf, 2*wf) << "\n";
   std::cout << "-> div(3*wi, 2*nz(wi))          = " << eve::div(3*wi, 2*nz(wi)) << "\n";
   std::cout << "-> div(3*wu, 2*nz(wu))          = " << eve::div(3*wu, 2*nz(wu)) << "\n";
   std::cout << "-> div(wt)                      = " << eve::div(wt) << "\n";
   std::cout << "-> div[ignore_last(2)](wf, 2*wf)= " << eve::div[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> div[wf != 0](wf, 2*wf)       = " << eve::div[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> div[upward](3*wf, 2*wf)      = " << eve::div[eve::upward](wf, 2*wf) << "\n";
   std::cout << "-> div[downward]3*(wf, 2*wf)    = " << eve::div[eve::downward](wf, 2*wf) << "\n";
   std::cout << "-> div[toward_zero](3*wf, 2*wf) = " << eve::div[eve::toward_zero](wf, 2*wf) << "\n";
   std::cout << "-> div[to_nearest](3*wf, 2*wf)  = " << eve::div[eve::to_nearest](wf, 2*wf) << "\n";
   std::cout << "-> div[saturated](3*wi, 2*wi)   = " << eve::div[eve::saturated](wi, 2*wi) << "\n";
}
