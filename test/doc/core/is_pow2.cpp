// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> is_pow2(wi)                = " << eve::is_pow2(wi) << "\n";
   std::cout << "-> is_pow2[ignore_last(2)](wi)= " << eve::is_pow2[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> is_pow2[wi != 0](wi)       = " << eve::is_pow2[wi != 0](wi) << "\n";
}
