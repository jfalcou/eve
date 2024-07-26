// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> byte_swap_pairs(wi, index_t<0>(), index_t<1>())                = " << eve::byte_swap_pairs(wi, eve::index_t<0>(), eve::index_t<1>()) << "\n";
   std::cout << "-> byte_swap_pairs[ignore_last(2)](wi, index_t<0>(), index_t<1>())= " << eve::byte_swap_pairs[eve::ignore_last(2)](wi, eve::index_t<0>(), eve::index_t<1>()) << "\n";
   std::cout << "-> byte_swap_pairs[wi != 0](wi, index_t<0>(), index_t<1>())       = " << eve::byte_swap_pairs[wi != 0](wi, eve::index_t<0>(), eve::index_t<1>()) << "\n";
}
