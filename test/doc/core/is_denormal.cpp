// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> is_denormal(wf)                = " << eve::is_denormal(wf) << "\n";
   std::cout << "-> is_denormal(wi)                = " << eve::is_denormal(wi) << "\n";
   std::cout << "-> is_denormal[ignore_last(2)](wf)= " << eve::is_denormal[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> is_denormal[wf != 0](wf)       = " << eve::is_denormal[wf != 0](wf) << "\n";
}
