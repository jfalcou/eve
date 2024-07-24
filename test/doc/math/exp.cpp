// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> exp(wf)                = " << eve::exp(wf) << "\n";
   std::cout << "-> exp[ignore_last(2)](wf)= " << eve::exp[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> exp[wf != -2.0f](wf)   = " << eve::exp[wf != -2.0f](wf) << "\n";
}
