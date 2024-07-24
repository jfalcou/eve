// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cotd(wf)                = " << eve::cotd(wf) << "\n";
   std::cout << "-> cotd[ignore_last(2)](wf)= " << eve::cotd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cotd[wf != -2.0f](wf)   = " << eve::cotd[wf != -2.0f](wf) << "\n";
   std::cout << "-> cotd[quarter_circle](wf)= " << eve::cotd[eve::quarter_circle](wf) << "\n";
   std::cout << "-> cotd[half_circle](wf)   = " << eve::cotd[eve::half_circle](wf) << "\n";
   std::cout << "-> cotd[full_circle](wf)   = " << eve::cotd[eve::full_circle](wf) << "\n";
}
