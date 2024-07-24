// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> div_180(wf)                = " << eve::div_180(wf) << "\n";
   std::cout << "-> div_180[ignore_last(2)](wf)= " << eve::div_180[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> div_180[wf != -2.0f](wf)   = " << eve::div_180[wf != -2.0f](wf) << "\n";
}
