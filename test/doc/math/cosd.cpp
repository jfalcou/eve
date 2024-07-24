// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cosd(wf)                = " << eve::cosd(wf) << "\n";
   std::cout << "-> cosd[ignore_last(2)](wf)= " << eve::cosd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cosd[wf != -2.0f](wf)   = " << eve::cosd[wf != -2.0f](wf) << "\n";
   std::cout << "-> cosd[quarter_circle](wf)= " << eve::cosd[eve::quarter_circle](wf) << "\n";
   std::cout << "-> cosd[half_circle](wf)   = " << eve::cosd[eve::half_circle](wf) << "\n";
   std::cout << "-> cosd[full_circle](wf)   = " << eve::cosd[eve::full_circle](wf) << "\n";
}
