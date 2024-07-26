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
 
   std::cout << "-> sign(wf)                = " << eve::sign(wf) << "\n";
   std::cout << "-> sign(wi)                = " << eve::sign(wi) << "\n";
   std::cout << "-> sign(wu)                = " << eve::sign(wu) << "\n";
   std::cout << "-> sign[ignore_last(2)](wf)= " << eve::sign[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sign[ignore_last(2)](wi)= " << eve::sign[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> sign[ignore_last(2)](wu)= " << eve::sign[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> sign[wf != 0](wf)       = " << eve::sign[wf != 0](wf) << "\n";
   std::cout << "-> sign[wi != 0](wi)       = " << eve::sign[wi != 0](wi) << "\n";
   std::cout << "-> sign[wu != 0](wu)       = " << eve::sign[wu != 0](wu) << "\n";
}
