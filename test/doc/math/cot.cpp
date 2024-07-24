// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cot(wf)                = " << eve::cot(wf) << "\n";
   std::cout << "-> cot[ignore_last(2)](wf)= " << eve::cot[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cot[wf != -2.0f](wf)   = " << eve::cot[wf != -2.0f](wf) << "\n";
   std::cout << "-> cot[quarter_circle](wf)= " << eve::cot[eve::quarter_circle](wf) << "\n";
   std::cout << "-> cot[half_circle](wf)   = " << eve::cot[eve::half_circle](wf) << "\n";
   std::cout << "-> cot[full_circle](wf)   = " << eve::cot[eve::full_circle](wf) << "\n";
}
