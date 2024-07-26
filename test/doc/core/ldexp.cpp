// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> ldexp(wf, 2*wi)                = " << eve::ldexp(wf, 2*wi) << "\n";
   std::cout << "-> ldexp[ignore_last(2)](wf, 2*wi)= " << eve::ldexp[eve::ignore_last(2)](wf, 2*wi) << "\n";
   std::cout << "-> ldexp[wf != 0](wf, 2*wi)       = " << eve::ldexp[wf != 0](wf, 2*wi) << "\n";
}
