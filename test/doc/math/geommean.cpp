// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
kumi::tuple wt{wf,2*wf,3*wf}; 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wt = " << wt << "\n"; 
 
   std::cout << "-> geommean(wf, 2*wf)                = " << eve::geommean(wf, 2*wf) << "\n";
   std::cout << "-> geommean(wt)                      = " << eve::geommean(wt) << "\n";
   std::cout << "-> geommean[ignore_last(2)](wf, 2*wf)= " << eve::geommean[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> geommean[wf != -2.0f](wf, 2*wf)   = " << eve::geommean[wf != -2.0f](wf, 2*wf) << "\n";
}
