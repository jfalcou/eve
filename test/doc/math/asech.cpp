// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> asech(wf)                = " << eve::asech(wf) << "\n";
   std::cout << "-> asech[ignore_last(2)](wf)= " << eve::asech[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> asech[wf != -2.0f](wf)   = " << eve::asech[wf != -2.0f](wf) << "\n";
}
