// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>
#if __has_include(<boost/math/special_functions/heuman_lambda.hpp>)
#include <boost/math/special_functions/heuman_lambda.hpp>
#define EVE_HAS_BOOST
#endif

auto hl = [](auto x, auto y) -> decltype(x) { return boost::math::heuman_lambda(y, x); };

eve::wide wf{0.9, 0.2, 0.75, 0.5};
eve::wide wphi{0.8, 1.0e-30, 0.5, 0.1};

int main(){
   std::cout << "<- wf   = " << wf << "\n";
   std::cout << "<- wphi = " << wphi << "\n";

   std::cout << "-> heuman_lambda(wphi, wf)               = " << eve::heuman_lambda(wphi, wf) << "\n";
   std::cout << "-> hl           (wphi, wf)               = " << eve::detail::map(hl, wphi, wf) << "\n";
   std::cout << "-> heuman_lambda[ignore_last(2)](wphi,wf)= " << eve::heuman_lambda[eve::ignore_last(2)](wphi, wf) << "\n";
   std::cout << "-> heuman_lambda[wf != 1.0](wphi,wf)     = " << eve::heuman_lambda[wf != -1.0f](wphi, wf) << "\n";
   std::cout << "-> heuman_lambda(pio_2[lower], wf)       = " << eve::heuman_lambda(eve::pio_2[eve::lower](eve::as(wphi)), wf) << '\n';
   std::cout << "-> heuman_lambda(pio_2[upper], wf)       = " << eve::heuman_lambda(eve::pio_2[eve::upper](eve::as(wphi)), wf) << '\n';
}
