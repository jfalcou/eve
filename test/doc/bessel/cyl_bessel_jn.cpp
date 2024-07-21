// revision 1
#include <eve/module/bessel.hpp>
#include <iostream>

eve::wide<double> wf([](auto i, auto c)->double{ return 2*(i-c/2);});
eve::wide<std::uint64_t> wu([](auto i, auto )->std::uint64_t{ return 2*i;});
eve::wide x{0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
eve::wide n{0.5, -1.0, 1.5, -2.0, 2.5, -2.6, 3.2, -12.0};

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- n  = " << n << "\n";
   std::cout << "<- x  = " << x << "\n";

   std::cout << "-> cyl_bessel_jn(wu, wf)                = " << eve::cyl_bessel_jn(wu, wf) << "\n";
   std::cout << "-> cyl_bessel_jn[ignore_last(2)](wu, wf)= " << eve::cyl_bessel_jn[eve::ignore_last(2)](wu, wf) << "\n";
   std::cout << "-> cyl_bessel_jn[wu != 2u](wu, wf)      = " << eve::cyl_bessel_jn[wu != 2u](wu, wf) << "\n";
   std::cout << "-> cyl_bessel_jn(n, x)                  = " << eve::cyl_bessel_jn(n, x) << "\n";
}
