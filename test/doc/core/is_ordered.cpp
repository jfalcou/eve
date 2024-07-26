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
 
   std::cout << "-> is_ordered(wf, 2*wf)                = " << eve::is_ordered(wf, 2*wf) << "\n";
   std::cout << "-> is_ordered(wi, 2*wi)                = " << eve::is_ordered(wi, 2*wi) << "\n";
   std::cout << "-> is_ordered(wu, 2*wu)                = " << eve::is_ordered(wu, 2*wu) << "\n";
   std::cout << "-> is_ordered[ignore_last(2)](wf, 2*wf)= " << eve::is_ordered[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> is_ordered[ignore_last(2)](wi, 2*wi)= " << eve::is_ordered[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> is_ordered[ignore_last(2)](wu, 2*wu)= " << eve::is_ordered[eve::ignore_last(2)](wu, 2*wu) << "\n";
   std::cout << "-> is_ordered[wf != 0](wf, 2*wf)       = " << eve::is_ordered[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> is_ordered[wi != 0](wi, 2*wi)       = " << eve::is_ordered[wi != 0](wi, 2*wi) << "\n";
   std::cout << "-> is_ordered[wu != 0](wu, 2*wu)       = " << eve::is_ordered[wu != 0](wu, 2*wu) << "\n";
}
