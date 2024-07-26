// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> firstbitset(wi)                = " << eve::firstbitset(wi) << "\n";
   std::cout << "-> firstbitset[ignore_last(2)](wi)= " << eve::firstbitset[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> firstbitset[wi != 0](wi)       = " << eve::firstbitset[wi != 0](wi) << "\n";
}
