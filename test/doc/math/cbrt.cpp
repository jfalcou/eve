// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cbrt(wf)                = " << eve::cbrt(wf) << "\n";
   std::cout << "-> cbrt[ignore_last(2)](wf)= " << eve::cbrt[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cbrt[wf != -2.0f](wf)   = " << eve::cbrt[wf != -2.0f](wf) << "\n";
}
