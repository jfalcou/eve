// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> ifrexp(wf)          = " << eve::ifrexp(wf) << "\n";
   std::cout << "-> ifrexp[pedantic](wf)= " << eve::ifrexp[eve::pedantic](wf) << "\n";
}
