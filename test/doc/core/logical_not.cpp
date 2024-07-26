// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> logical_not(wu <= maximum(wu)/2)= " << eve::logical_not(wu <= eve::maximum(wu)/2) << "\n";
}
