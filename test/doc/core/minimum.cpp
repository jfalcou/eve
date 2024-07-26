// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> minimum(wf)                = " << eve::minimum(wf) << "\n";
   std::cout << "-> minimum(wi)                = " << eve::minimum(wi) << "\n";
   std::cout << "-> minimum(wu)                = " << eve::minimum(wu) << "\n";
   std::cout << "-> minimum[ignore_last(2)](wf)= " << eve::minimum[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> minimum[ignore_last(2)](wi)= " << eve::minimum[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> minimum[ignore_last(2)](wu)= " << eve::minimum[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> minimum[wf != -2.0f](wf)   = " << eve::minimum[wf != -2.0f](wf) << "\n";
   std::cout << "-> minimum[wi != -2](wi)      = " << eve::minimum[wi != -2](wi) << "\n";
   std::cout << "-> minimum[wu != 2u](wu)      = " << eve::minimum[wu != 2u](wu) << "\n";
}
