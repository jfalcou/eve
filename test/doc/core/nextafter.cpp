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
 
   std::cout << "-> nextafter(wf, 2*wf)                = " << eve::nextafter(wf, 2*wf) << "\n";
   std::cout << "-> nextafter(wi, 2*wi)                = " << eve::nextafter(wi, 2*wi) << "\n";
   std::cout << "-> nextafter(wu, 2*wu)                = " << eve::nextafter(wu, 2*wu) << "\n";
   std::cout << "-> nextafter[ignore_last(2)](wf, 2*wf)= " << eve::nextafter[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> nextafter[wf != 0](wf, 2*wf)       = " << eve::nextafter[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> nextafter[pedantic](wf, 2*wf)      = " << eve::nextafter[eve::pedantic](wf, 2*wf) << "\n";
}
