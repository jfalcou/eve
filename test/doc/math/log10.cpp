// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> log10(wf)                = " << eve::log10(wf) << "\n";
   std::cout << "-> log10[ignore_last(2)](wf)= " << eve::log10[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> log10[wf != -2.0f](wf)   = " << eve::log10[wf != -2.0f](wf) << "\n";
}
