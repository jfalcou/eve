// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acotd(wf)                = " << eve::acotd(wf) << "\n";
   std::cout << "-> acotd[ignore_last(2)](wf)= " << eve::acotd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acotd[wf != -2.0f](wf)   = " << eve::acotd[wf != -2.0f](wf) << "\n";
}
