// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> maximum(wf)                = " << eve::maximum(wf) << "\n";
   std::cout << "-> maximum(wi)                = " << eve::maximum(wi) << "\n";
   std::cout << "-> maximum(wu)                = " << eve::maximum(wu) << "\n";
   std::cout << "-> maximum[ignore_last(2)](wf)= " << eve::maximum[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> maximum[ignore_last(2)](wi)= " << eve::maximum[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> maximum[ignore_last(2)](wu)= " << eve::maximum[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> maximum[wf != -2.0f](wf)   = " << eve::maximum[wf != -2.0f](wf) << "\n";
   std::cout << "-> maximum[wi != -2](wi)      = " << eve::maximum[wi != -2](wi) << "\n";
   std::cout << "-> maximum[wu != 2u](wu)      = " << eve::maximum[wu != 2u](wu) << "\n";
}
