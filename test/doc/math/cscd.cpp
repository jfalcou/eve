// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cscd(wf)                = " << eve::cscd(wf) << "\n";
   std::cout << "-> cscd[ignore_last(2)](wf)= " << eve::cscd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cscd[wf != -2.0f](wf)   = " << eve::cscd[wf != -2.0f](wf) << "\n";
   std::cout << "-> cscd[quarter_circle](wf)= " << eve::cscd[eve::quarter_circle](wf) << "\n";
   std::cout << "-> cscd[half_circle](wf)   = " << eve::cscd[eve::half_circle](wf) << "\n";
   std::cout << "-> cscd[full_circle](wf)   = " << eve::cscd[eve::full_circle](wf) << "\n";
}
