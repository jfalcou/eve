// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide wf{1.0, 0.0, 0.75, 0.5};
eve::wide wphi{1.0, 1.0e-30, 0.5, 0.0};

int main(){
   std::cout << "<- wf   = " << wf << "\n";
   std::cout << "<- wphi = " << wphi << "\n";

   std::cout << "-> ellint_fe(wf)                = " << eve::ellint_fe(wf) << "\n";
   std::cout << "-> ellint_fe(wphi, wf)          = " << eve::ellint_fe(wphi, wf) << "\n";
}
