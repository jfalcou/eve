// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2; });
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i+1;});

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n";

   auto nz = [](auto wi){return eve::if_else(wi, wi, eve::one); };
   std::cout << "-> rem(wf, 2*wf)                = " << eve::rem(wf, 2*wf) << "\n";
   std::cout << "-> rem(wi, 2*nz(wi)             = " << eve::rem(wi, 2*nz(wi)) << "\n";
   std::cout << "-> rem(wu, 2*wu)                = " << eve::rem(wu, 2*nz(wu)) << "\n";
   std::cout << "-> rem[ignore_last(2)](wf, 2*wf)= " << eve::rem[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> rem[ignore_last(2)](wi, 2*wi)= " << eve::rem[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> rem[ignore_last(2)](wu, 2*wu)= " << eve::rem[eve::ignore_last(2)](wu, 2*wu) << "\n";
   std::cout << "-> rem[wf != 0](wf, 2*wf)       = " << eve::rem[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> rem[wi != 0](wi, 2*nz(wi)    = " << eve::rem[wi != 0](wi, 2*nz(wi)) << "\n";
   std::cout << "-> rem[wu != 0](wu, 2*wu        = " << eve::rem[wu != 0](wu, 2*wu) << "\n";
   std::cout << "-> rem[downward](wf, 2*wf)      = " << eve::rem[eve::downward](wf, 2*wf) << "\n";
   std::cout << "-> rem[upward](wf, 2*wf)        = " << eve::rem[eve::upward](wf, 2*wf) << "\n";
   std::cout << "-> rem[to_nearest](wf, 2*wf)    = " << eve::rem[eve::to_nearest](wf, 2*wf) << "\n";
   std::cout << "-> rem[toward_zero](wf, 2*wf)   = " << eve::rem[eve::toward_zero](wf, 2*wf) << "\n";
}
