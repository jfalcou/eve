// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> bit_shl(wi, 2*wi)                = " << eve::bit_shl(wi, 2*wi) << "\n";
   std::cout << "-> bit_shl[ignore_last(2)](wi, 2*wi)= " << eve::bit_shl[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> bit_shl[wi != 0](wi, 2*wi)       = " << eve::bit_shl[wi != 0](wi, 2*wi) << "\n";
}
