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
 
   std::cout << "-> next(wf)                = " << eve::next(wf) << "\n";
   std::cout << "-> next(wi)                = " << eve::next(wi) << "\n";
   std::cout << "-> next(wu)                = " << eve::next(wu) << "\n";
   std::cout << "-> next(wf, 2*wi)          = " << eve::next(wf, 2*wi) << "\n";
   std::cout << "-> next(wi, 2*wi)          = " << eve::next(wi, 2*wi) << "\n";
   std::cout << "-> next(wu, 2*wi)          = " << eve::next(wu, 2*wi) << "\n";
   std::cout << "-> next[ignore_last(2)](wf)= " << eve::next[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> next[wf != 0](wf)       = " << eve::next[wf != 0](wf) << "\n";
   std::cout << "-> next[pedantic](wf)      = " << eve::next[eve::pedantic](wf) << "\n";
   std::cout << "-> next[saturated ](wf)    = " << eve::next[eve::saturated ](wf) << "\n";
}
