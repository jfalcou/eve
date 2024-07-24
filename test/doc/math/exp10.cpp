// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> exp10(wf)                = " << eve::exp10(wf) << "\n";
   std::cout << "-> exp10[ignore_last(2)](wf)= " << eve::exp10[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> exp10[wf != -2.0f](wf)   = " << eve::exp10[wf != -2.0f](wf) << "\n";
}
