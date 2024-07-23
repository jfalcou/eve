// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> rising_factorial(wf, 2*wf)                = " << eve::rising_factorial(wf, 2*wf) << "\n";
   std::cout << "-> rising_factorial[ignore_last(2)](wf, 2*wf)= " << eve::rising_factorial[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> rising_factorial[wf != -2.0f](wf, 2*wf)   = " << eve::rising_factorial[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> rising_factorial[raw](wf, 2*wf)           = " << eve::rising_factorial[eve::raw](wf, 2*wf) << "\n";
   std::cout << "-> rising_factorial[pedantic](wf, 2*wf)      = " << eve::rising_factorial[eve::pedantic](wf, 2*wf) << "\n";
}
