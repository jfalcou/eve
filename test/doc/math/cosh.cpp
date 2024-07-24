// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cosh(wf)                = " << eve::cosh(wf) << "\n";
   std::cout << "-> cosh[ignore_last(2)](wf)= " << eve::cosh[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cosh[wf != -2.0f](wf)   = " << eve::cosh[wf != -2.0f](wf) << "\n";
}
