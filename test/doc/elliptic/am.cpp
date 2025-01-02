// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide wf{1.0, 0.0, 0.75, 0.5};
eve::wide wphi{1.0, 1.0e-30, 0.5, 0.0};

int main(){
   std::cout << "<- wf   = " << wf << "\n";
   std::cout << "<- wphi = " << wphi << "\n";

   std::cout << "-> am(wphi, wf)               = " << eve::am(wphi, wf) << "\n";
   std::cout << "-> am[ignore_last(2)](wphi,wf)= " << eve::am[eve::ignore_last(2)](wphi, wf) << "\n";
   std::cout << "-> am[wf != 1.0](wphi,wf)     = " << eve::am[wf != -1.0f](wphi, wf) << "\n";
   std::cout << "-> am(pio_2[lower], wf)       = " << eve::am(eve::pio_2[eve::lower](eve::as(wphi)), wf) << '\n';
   std::cout << "-> am(pio_2[upper], wf)       = " << eve::am(eve::pio_2[eve::upper](eve::as(wphi)), wf) << '\n';
}
