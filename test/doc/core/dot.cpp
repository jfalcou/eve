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
 
   std::cout << "-> dot(wf, 2*wf)= " << eve::dot(wf, 2*wf) << "\n";
   std::cout << "-> dot(wi, 2*wi)= " << eve::dot(wi, 2*wi) << "\n";
   std::cout << "-> dot(wu, 2*wu)= " << eve::dot(wu, 2*wu) << "\n";
}
