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
 
   std::cout << "-> is_eqz(wf)                = " << eve::is_eqz(wf) << "\n";
   std::cout << "-> is_eqz(wi)                = " << eve::is_eqz(wi) << "\n";
   std::cout << "-> is_eqz(wu)                = " << eve::is_eqz(wu) << "\n";
   std::cout << "-> is_eqz[ignore_last(2)](wf)= " << eve::is_eqz[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> is_eqz[ignore_last(2)](wi)= " << eve::is_eqz[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> is_eqz[ignore_last(2)](wu)= " << eve::is_eqz[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> is_eqz[wf != 0](wf)       = " << eve::is_eqz[wf != 0](wf) << "\n";
   std::cout << "-> is_eqz[wi != 0](wi)       = " << eve::is_eqz[wi != 0](wi) << "\n";
   std::cout << "-> is_eqz[wu != 0](wu)       = " << eve::is_eqz[wu != 0](wu) << "\n";
}
