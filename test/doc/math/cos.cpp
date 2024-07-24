// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cos(wf)                = " << eve::cos(wf) << "\n";
   std::cout << "-> cos[ignore_last(2)](wf)= " << eve::cos[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cos[wf != -2.0f](wf)   = " << eve::cos[wf != -2.0f](wf) << "\n";
   std::cout << "-> cos[quarter_circle](wf)= " << eve::cos[eve::quarter_circle](wf) << "\n";
   std::cout << "-> cos[half_circle](wf)   = " << eve::cos[eve::half_circle](wf) << "\n";
   std::cout << "-> cos[full_circle](wf)   = " << eve::cos[eve::full_circle](wf) << "\n";
}
