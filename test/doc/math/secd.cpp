// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> secd(wf)                = " << eve::secd(wf) << "\n";
   std::cout << "-> secd[ignore_last(2)](wf)= " << eve::secd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> secd[wf != -2.0f](wf)   = " << eve::secd[wf != -2.0f](wf) << "\n";
   std::cout << "-> secd[quarter_circle](wf)= " << eve::secd[eve::quarter_circle](wf) << "\n";
   std::cout << "-> secd[half_circle](wf)   = " << eve::secd[eve::half_circle](wf) << "\n";
   std::cout << "-> secd[full_circle](wf)   = " << eve::secd[eve::full_circle](wf) << "\n";
}
