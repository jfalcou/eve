// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide wf{1.0, 0.0, 0.75, 0.5};;
eve::wide wphi{1.0, 1.0e-30, 0.5, 0.0};

int main(){
  std::cout << "<- wf   = " << wf << "\n";
  std::cout << "<- wphi = " << wphi << "\n";

  std::cout << "-> ellint_d(wf)                = " << eve::ellint_d(wf) << "\n";
  std::cout << "-> ellint_d(wphi, wf)          = " << eve::ellint_d(wphi, wf) << "\n";
  std::cout << "-> ellint_d[ignore_last(2)](wf)= " << eve::ellint_d[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> ellint_d[wf != 1.0](wf)     = " << eve::ellint_d[wf != -1.0f](wf) << "\n";
  std::cout << "-> ellint_d(pio_2[lower],wf)   = " << eve::ellint_d(eve::pio_2[eve::lower](eve::as(wphi)), wf) << '\n';
}
