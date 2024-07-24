// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

eve::wide<float> wf([](auto i, auto c)->float{ return (1+eve::eps(eve::as<float>()))*(i-c/2);});
kumi::tuple wtc{wf,2*wf,3*wf};
kumi::tuple wtn{4*wf, 5*wf};


int main()
{
   std::cout << std::setprecision(10);
   std::cout << "<- wf  = " << wf << "\n";
   std::cout << "<- wtc = " << wtc << "\n";
   std::cout << "<- wtn = " << wtn << "\n";

   std::cout << "-> newton(wf,wf,2*wf,3*wf,4*wf,5*wf)           = " << eve::newton(wf,wf,2*wf,3*wf,4*wf,5*wf) << "\n";
   std::cout << "-> newton(wf,wtc,wtn)                          = " << eve::newton(wf, wtc,wtn) << "\n";
   std::cout << "-> newton[pedantic](wf,wf,2*wf,3*wf,4*wf, 5*wf)= " << eve::newton[eve::pedantic](wf,wf,2*wf,3*wf,4*wf, 5*wf) << "\n";
}
