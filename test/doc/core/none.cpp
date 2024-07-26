// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> none(wu <= maximum(wu)/2)                = " << eve::none(wu <= eve::maximum(wu)/2) << "\n";
   std::cout << "-> none[ignore_last(2)](wu <= maximum(wu)/2)= " << eve::none[eve::ignore_last(2)](wu <= eve::maximum(wu)/2) << "\n";
}
