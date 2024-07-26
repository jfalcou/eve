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
 
   std::cout << "-> is_lessgreater(wf, 2*wf)                = " << eve::is_lessgreater(wf, 2*wf) << "\n";
   std::cout << "-> is_lessgreater(wi, 2*wi)                = " << eve::is_lessgreater(wi, 2*wi) << "\n";
   std::cout << "-> is_lessgreater(wu, 2*wu)                = " << eve::is_lessgreater(wu, 2*wu) << "\n";
   std::cout << "-> is_lessgreater[ignore_last(2)](wf, 2*wf)= " << eve::is_lessgreater[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> is_lessgreater[ignore_last(2)](wi, 2*wi)= " << eve::is_lessgreater[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> is_lessgreater[ignore_last(2)](wu, 2*wu)= " << eve::is_lessgreater[eve::ignore_last(2)](wu, 2*wu) << "\n";
   std::cout << "-> is_lessgreater[wf != 0](wf, 2*wf)       = " << eve::is_lessgreater[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> is_lessgreater[wi != 0](wi, 2*wi)       = " << eve::is_lessgreater[wi != 0](wi, 2*wi) << "\n";
   std::cout << "-> is_lessgreater[wu != 0](wu, 2*wu)       = " << eve::is_lessgreater[wu != 0](wu, 2*wu) << "\n";
}
