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
 
   std::cout << "-> sqrt(wf)                = " << eve::sqrt(wf) << "\n";
   std::cout << "-> sqrt(wi)                = " << eve::sqrt(wi) << "\n";
   std::cout << "-> sqrt(wu)                = " << eve::sqrt(wu) << "\n";
   std::cout << "-> sqrt[ignore_last(2)](wf)= " << eve::sqrt[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sqrt[ignore_last(2)](wi)= " << eve::sqrt[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> sqrt[ignore_last(2)](wu)= " << eve::sqrt[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> sqrt[wf != 0](wf)       = " << eve::sqrt[wf != 0](wf) << "\n";
   std::cout << "-> sqrt[wi != 0](wi)       = " << eve::sqrt[wi != 0](wi) << "\n";
   std::cout << "-> sqrt[wu != 0](wu)       = " << eve::sqrt[wu != 0](wu) << "\n";
   std::cout << "-> sqrt[raw](wf)           = " << eve::sqrt[eve::raw](wf) << "\n";
   std::cout << "-> sqrt[raw](wi)           = " << eve::sqrt[eve::raw](wi) << "\n";
   std::cout << "-> sqrt[raw](wu)           = " << eve::sqrt[eve::raw](wu) << "\n";
}
