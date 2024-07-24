// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> agd(wf)                = " << eve::agd(wf) << "\n";
   std::cout << "-> agd[ignore_last(2)](wf)= " << eve::agd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> agd[wf != -2.0f](wf)   = " << eve::agd[wf != -2.0f](wf) << "\n";
}
