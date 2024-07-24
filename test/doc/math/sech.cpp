// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sech(wf)                = " << eve::sech(wf) << "\n";
   std::cout << "-> sech[ignore_last(2)](wf)= " << eve::sech[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sech[wf != -2.0f](wf)   = " << eve::sech[wf != -2.0f](wf) << "\n";
}
