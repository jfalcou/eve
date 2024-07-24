// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wu = " << wu << "\n";

   std::cout << "-> pow(wf, 2*wf)                = " << eve::pow(wf, 2*wf) << "\n";
   std::cout << "-> pow(wu, 2*wu)                = " << eve::pow(wu, 2*wu) << "\n";
   std::cout << "-> pow[ignore_last(2)](wf, 2*wf)= " << eve::pow[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> pow[ignore_last(2)](wu, 2*wu)= " << eve::pow[eve::ignore_last(2)](wu, 2*wu) << "\n";
   std::cout << "-> pow[wf != -2.0f](wf, 2*wf)   = " << eve::pow[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> pow[wu != 2u](wu, 2*wu)      = " << eve::pow[wu != 2u](wu, 2*wu) << "\n";
   std::cout << "-> pow[raw](wf, 2*wf)           = " << eve::pow[eve::raw](wf, 2*wf) << "\n";
   std::cout << "-> pow[raw](wu, 2*wu)           = " << eve::pow[eve::raw](wu, 2*wu) << "\n";
}
