// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> expm1(wf)                = " << eve::expm1(wf) << "\n";
   std::cout << "-> expm1[ignore_last(2)](wf)= " << eve::expm1[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> expm1[wf != -2.0f](wf)   = " << eve::expm1[wf != -2.0f](wf) << "\n";
}
