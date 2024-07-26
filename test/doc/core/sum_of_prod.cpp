// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sum_of_prod(wf, 2*wf, 3*wf, 4*wf)                = " << eve::sum_of_prod(wf, 2*wf, 3*wf, 4*wf) << "\n";
   std::cout << "-> sum_of_prod[ignore_last(2)](wf, 2*wf, 3*wf, 4*wf)= " << eve::sum_of_prod[eve::ignore_last(2)](wf, 2*wf, 3*wf, 4*wf) << "\n";
   std::cout << "-> sum_of_prod[raw](wf, 2*wf, 3*wf, 4*wf)           = " << eve::sum_of_prod[eve::raw](wf, 2*wf, 3*wf, 4*wf) << "\n";
   std::cout << "-> sum_of_prod[pedantic](wf, 2*wf, 3*wf, 4*wf)      = " << eve::sum_of_prod[eve::pedantic](wf, 2*wf, 3*wf, 4*wf) << "\n";
}
