// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> any(wu <= maximum(wu)/2)                = " << eve::any(wu <= eve::maximum(wu)/2) << "\n";
   std::cout << "-> any[ignore_last(2)](wu <= maximum(wu)/2)= " << eve::any[eve::ignore_last(2)](wu <= eve::maximum(wu)/2) << "\n";
}
