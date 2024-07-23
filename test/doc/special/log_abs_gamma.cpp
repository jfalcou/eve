// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> log_abs_gamma(wf)                = " << eve::log_abs_gamma(wf) << "\n";
   std::cout << "-> log_abs_gamma[ignore_last(2)](wf)= " << eve::log_abs_gamma[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> log_abs_gamma[wf != -2.0f](wf)   = " << eve::log_abs_gamma[wf != -2.0f](wf) << "\n";
}
