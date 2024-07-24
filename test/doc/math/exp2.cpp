// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> exp2(wf)                = " << eve::exp2(wf) << "\n";
   std::cout << "-> exp2(wi)                = " << eve::exp2(wi) << "\n";
   std::cout << "-> exp2(wu)                = " << eve::exp2(wu) << "\n";
   std::cout << "-> exp2[ignore_last(2)](wf)= " << eve::exp2[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> exp2[ignore_last(2)](wi)= " << eve::exp2[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> exp2[ignore_last(2)](wu)= " << eve::exp2[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> exp2[wf != -2.0f](wf)   = " << eve::exp2[wf != -2.0f](wf) << "\n";
   std::cout << "-> exp2[wi != -2](wi)      = " << eve::exp2[wi != -2](wi) << "\n";
   std::cout << "-> exp2[wu != 2u](wu)      = " << eve::exp2[wu != 2u](wu) << "\n";
}
