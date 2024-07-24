// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> csc(wf)                = " << eve::csc(wf) << "\n";
   std::cout << "-> csc[ignore_last(2)](wf)= " << eve::csc[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> csc[wf != -2.0f](wf)   = " << eve::csc[wf != -2.0f](wf) << "\n";
   std::cout << "-> csc[quarter_circle](wf)= " << eve::csc[eve::quarter_circle](wf) << "\n";
   std::cout << "-> csc[half_circle](wf)   = " << eve::csc[eve::half_circle](wf) << "\n";
   std::cout << "-> csc[full_circle](wf)   = " << eve::csc[eve::full_circle](wf) << "\n";
}
