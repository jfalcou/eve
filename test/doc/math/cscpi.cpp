// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cscpi(wf)                = " << eve::cscpi(wf) << "\n";
   std::cout << "-> cscpi[ignore_last(2)](wf)= " << eve::cscpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cscpi[wf != -2.0f](wf)   = " << eve::cscpi[wf != -2.0f](wf) << "\n";
   std::cout << "-> cscpi[quarter_circle](wf)= " << eve::cscpi[eve::quarter_circle](wf) << "\n";
   std::cout << "-> cscpi[half_circle](wf)   = " << eve::cscpi[eve::half_circle](wf) << "\n";
   std::cout << "-> cscpi[full_circle](wf)   = " << eve::cscpi[eve::full_circle](wf) << "\n";
}
