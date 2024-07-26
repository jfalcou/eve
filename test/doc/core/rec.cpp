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
 
   std::cout << "-> rec(wf)                = " << eve::rec(wf) << "\n";
   std::cout << "-> rec(wi)                = " << eve::rec(wi) << "\n";
   std::cout << "-> rec(wu)                = " << eve::rec(wu) << "\n";
   std::cout << "-> rec[ignore_last(2)](wf)= " << eve::rec[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> rec[ignore_last(2)](wi)= " << eve::rec[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> rec[ignore_last(2)](wu)= " << eve::rec[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> rec[wf != 0](wf)       = " << eve::rec[wf != 0](wf) << "\n";
   std::cout << "-> rec[wi != 0](wi)       = " << eve::rec[wi != 0](wi) << "\n";
   std::cout << "-> rec[wu != 0](wu)       = " << eve::rec[wu != 0](wu) << "\n";
   std::cout << "-> rec[raw](wf)           = " << eve::rec[eve::raw](wf) << "\n";
   std::cout << "-> rec[raw](wi)           = " << eve::rec[eve::raw](wi) << "\n";
   std::cout << "-> rec[raw](wu)           = " << eve::rec[eve::raw](wu) << "\n";
   std::cout << "-> rec[pedantic](wf)      = " << eve::rec[eve::pedantic](wf) << "\n";
   std::cout << "-> rec[pedantic](wi)      = " << eve::rec[eve::pedantic](wi) << "\n";
   std::cout << "-> rec[pedantic](wu)      = " << eve::rec[eve::pedantic](wu) << "\n";
}
