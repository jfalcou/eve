// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

eve::wide<float> wf([](auto i, auto c)->float{ return (1+eve::eps(eve::as<float>()))*(i-c/2);});
kumi::tuple wt{wf,2*wf,3*wf};

int main(){
   std::cout << std::setprecision(10);
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wt = " << wt << "\n";

   std::cout << "-> reverse_horner(wf, wf, 2*wf, 3*wf)          = " << eve::reverse_horner(wf, wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> reverse_horner(wf, wt)                      = " << eve::reverse_horner(wf, wt) << "\n";
   std::cout << "-> reverse_horner[pedantic](wf, wf, 2*wf, 3*w) = " << eve::reverse_horner[eve::pedantic](wf, wf, 2*wf, 3*wf) << "\n";
}
