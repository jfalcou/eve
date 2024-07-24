// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> log_abs(wf)                = " << eve::log_abs(wf) << "\n";
   std::cout << "-> log_abs[ignore_last(2)](wf)= " << eve::log_abs[eve::ignore_last(2)](wf) << "\n";
}
