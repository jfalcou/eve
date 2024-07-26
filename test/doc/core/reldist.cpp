// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> reldist(wf, 2*wf)                = " << eve::reldist(wf, 2*wf) << "\n";
   std::cout << "-> reldist[ignore_last(2)](wf, 2*wf)= " << eve::reldist[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> reldist[wf != 0](wf, 2*wf)       = " << eve::reldist[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> reldist[pedantic](wf, 2*wf)      = " << eve::reldist[eve::pedantic](wf, 2*wf) << "\n";
}
