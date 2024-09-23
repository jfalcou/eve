// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide wf{1.0, 0.0, 0.75, 0.5};;
eve::wide wphi{1.0, 1.0e-30, 0.5, 0.0};

int main(){
   std::cout << "<- wf   = " << wf << "\n";
   std::cout << "<- wphi = " << wphi << "\n";

   std::cout << "-> ellint_2(wf)                = " << eve::ellint_2(wf) << "\n";
   std::cout << "-> ellint_2(wphi, wf)          = " << eve::ellint_2(wphi, wf) << "\n";
   std::cout << "-> ellint_2[ignore_last(2)](wf)= " << eve::ellint_2[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> ellint_2[wf != 1.0](wf)     = " << eve::ellint_2[wf != -1.0f](wf) << "\n";
   std::cout << "-> ellint_2(pio_2,wf)          = " << eve::ellint_2(eve::pio_2[eve::lower](eve::as(wphi)), wf) << '\n';
}
