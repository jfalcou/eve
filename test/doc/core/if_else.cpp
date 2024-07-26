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
 
   std::cout << "-> if_else(wf, 2*wf, 3*wf)= " << eve::if_else(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> if_else(wi, 2*wi, 3*wi)= " << eve::if_else(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> if_else(wu, 2*wu, 3*wu)= " << eve::if_else(wu, 2*wu, 3*wu) << "\n";
}
