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
 
   std::cout << "-> trunc(wf)                = " << eve::trunc(wf) << "\n";
   std::cout << "-> trunc(wi)                = " << eve::trunc(wi) << "\n";
   std::cout << "-> trunc(wu)                = " << eve::trunc(wu) << "\n";
   std::cout << "-> trunc[ignore_last(2)](wf)= " << eve::trunc[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> trunc[ignore_last(2)](wi)= " << eve::trunc[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> trunc[ignore_last(2)](wu)= " << eve::trunc[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> trunc[wf != 0](wf)       = " << eve::trunc[wf != 0](wf) << "\n";
   std::cout << "-> trunc[wi != 0](wi)       = " << eve::trunc[wi != 0](wi) << "\n";
   std::cout << "-> trunc[wu != 0](wu)       = " << eve::trunc[wu != 0](wu) << "\n";
   std::cout << "-> trunc[almost](wf)        = " << eve::trunc[eve::almost](wf) << "\n";
   std::cout << "-> trunc[raw](wf)           = " << eve::trunc[eve::raw](wf) << "\n";
}
