// revision 1
#include <eve/module/bessel.hpp>
#include <iostream>


eve::wide<double> wf([](auto i, auto c)->double{ return 2*(i+c/2);});
eve::wide<std::uint64_t> wu([](auto i, auto )->std::uint64_t{ return 2*i;});
eve::wide w{0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
eve::wide m{0.5, -1.0, 1.5, -2.0, 2.5, -2.6, 3.2, -12.0};

int main()
{
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- m  = " << m << "\n";
   std::cout << "<- w  = " << w << "\n";

   std::cout << "-> cyl_bessel_kn(wu, wf)                = " << eve::cyl_bessel_kn(wu, wf) << "\n";
   std::cout << "-> cyl_bessel_kn[ignore_last(2)](wu, wf)= " << eve::cyl_bessel_kn[eve::ignore_last(2)](wu, wf) << "\n";
   std::cout << "-> cyl_bessel_kn[wu != 2u](wu, wf)      = " << eve::cyl_bessel_kn[wu != 2u](wu, wf) << "\n";
   std::cout << "-> cyl_bessel_kn(m, w)                  = " << eve::cyl_bessel_kn(m, w) << "\n";
}
