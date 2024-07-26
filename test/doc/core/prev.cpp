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
 
   std::cout << "-> prev(wf)                = " << eve::prev(wf) << "\n";
   std::cout << "-> prev(wi)                = " << eve::prev(wi) << "\n";
   std::cout << "-> prev(wu)                = " << eve::prev(wu) << "\n";
   std::cout << "-> prev(wf, 2*wi)          = " << eve::prev(wf, 2*wi) << "\n";
   std::cout << "-> prev(wi, 2*wi)          = " << eve::prev(wi, 2*wi) << "\n";
   std::cout << "-> prev(wu, 2*wi)          = " << eve::prev(wu, 2*wi) << "\n";
   std::cout << "-> prev[ignore_last(2)](wf)= " << eve::prev[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> prev[wf != 0](wf)       = " << eve::prev[wf != 0](wf) << "\n";
   std::cout << "-> prev[pedantic](wf)      = " << eve::prev[eve::pedantic](wf) << "\n";
   std::cout << "-> prev[saturated ](wf)    = " << eve::prev[eve::saturated ](wf) << "\n";
}
