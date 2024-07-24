// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sec(wf)                = " << eve::sec(wf) << "\n";
   std::cout << "-> sec[ignore_last(2)](wf)= " << eve::sec[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sec[wf != -2.0f](wf)   = " << eve::sec[wf != -2.0f](wf) << "\n";
   std::cout << "-> sec[quarter_circle](wf)= " << eve::sec[eve::quarter_circle](wf) << "\n";
   std::cout << "-> sec[half_circle](wf)   = " << eve::sec[eve::half_circle](wf) << "\n";
   std::cout << "-> sec[full_circle](wf)   = " << eve::sec[eve::full_circle](wf) << "\n";
}
