// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return eve::pi(eve::as < float>())*2*(i-c/2);});

int main(){
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> rempio2(wf)                = " << eve::rempio2(wf) << "\n";
   std::cout << "-> rempio2[quarter_circle](wf)= " << eve::rempio2[eve::quarter_circle](wf) << "\n";
   std::cout << "-> rempio2[half_circle](wf)   = " << eve::rempio2[eve::half_circle](wf) << "\n";
   std::cout << "-> rempio2[full_circle](wf)   = " << eve::rempio2[eve::full_circle](wf) << "\n";
   std::cout << "-> rempio2[medium](wf)        = " << eve::rempio2[eve::medium2](wf) << "\n";
   std::cout << "-> rempio2[big](wf)           = " << eve::rempio2[eve::big2](wf) << "\n";
}
