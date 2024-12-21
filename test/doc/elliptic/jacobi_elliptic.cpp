// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide wf{1.0, 0.0, 0.75, 0.5};
eve::wide wphi{1.0, 1.0e-30, 0.5, 0.0};

int main(){
   std::cout << "<- wf   =                              " << wf << "\n";
   std::cout << "<- wphi =                              " << wphi << "\n";
   auto [sn, cn, dn] = eve::jacobi_elliptic(wphi, wf);
   std::cout << "-> sn =                                " << sn << std::endl;
   std::cout << "-> cn =                                " << cn << std::endl;
   std::cout << "-> dn =                                " << dn << std::endl;
   std::cout << "-> jacobi_elliptic(pio_2[lower], wf) = " << eve::jacobi_elliptic(eve::pio_2[eve::lower](eve::as(wphi)), wf) << '\n';
   std::cout << "-> jacobi_elliptic(pio_2[upper], wf) = " << eve::jacobi_elliptic(eve::pio_2[eve::upper](eve::as(wphi)), wf) << '\n';
}
