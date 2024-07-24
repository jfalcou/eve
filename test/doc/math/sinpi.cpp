// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sinpi(wf)                = " << eve::sinpi(wf) << "\n";
   std::cout << "-> sinpi[ignore_last(2)](wf)= " << eve::sinpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sinpi[wf != -2.0f](wf)   = " << eve::sinpi[wf != -2.0f](wf) << "\n";
   std::cout << "-> sinpi[quarter_circle](wf)= " << eve::sinpi[eve::quarter_circle](wf) << "\n";
   std::cout << "-> sinpi[half_circle](wf)   = " << eve::sinpi[eve::half_circle](wf) << "\n";
   std::cout << "-> sinpi[full_circle](wf)   = " << eve::sinpi[eve::full_circle](wf) << "\n";
}
