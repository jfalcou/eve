// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> log1p(wf)                = " << eve::log1p(wf) << "\n";
   std::cout << "-> log1p[ignore_last(2)](wf)= " << eve::log1p[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> log1p[wf != -2.0f](wf)   = " << eve::log1p[wf != -2.0f](wf) << "\n";
}
