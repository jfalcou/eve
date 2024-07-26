// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> shl(wi, 2*wi)                = " << eve::shl(wi, 2*wi) << "\n";
   std::cout << "-> shl(wi, index_t<0>())        = " << eve::shl(wi, eve::index_t<0>()) << "\n";
   std::cout << "-> shl[ignore_last(2)](wi, 2*wi)= " << eve::shl[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> shl[wi != 0](wi, 2*wi)       = " << eve::shl[wi != 0](wi, 2*wi) << "\n";
}
