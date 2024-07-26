// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> rsqrt(wf)                = " << eve::rsqrt(wf) << "\n";
   std::cout << "-> rsqrt[ignore_last(2)](wf)= " << eve::rsqrt[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> rsqrt[wf != 0](wf)       = " << eve::rsqrt[wf != 0](wf) << "\n";
   std::cout << "-> rsqrt[raw](wf)           = " << eve::rsqrt[eve::raw](wf) << "\n";
}
