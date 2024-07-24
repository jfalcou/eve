// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> asinh(wf)                = " << eve::asinh(wf) << "\n";
   std::cout << "-> asinh[ignore_last(2)](wf)= " << eve::asinh[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> asinh[wf != -2.0f](wf)   = " << eve::asinh[wf != -2.0f](wf) << "\n";
}
