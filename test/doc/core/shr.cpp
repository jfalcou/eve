// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> shr(wi, 2*wi)                = " << eve::shr(wi, 2*wi) << "\n";
   std::cout << "-> shr(wi, index_t<0>())        = " << eve::shr(wi, eve::index_t<0>()) << "\n";
   std::cout << "-> shr[ignore_last(2)](wi, 2*wi)= " << eve::shr[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> shr[wi != 0](wi, 2*wi)       = " << eve::shr[wi != 0](wi, 2*wi) << "\n";
}
