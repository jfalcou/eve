// revision 1
#include <eve/module/bessel.hpp>
#include <iostream>

int main()
{
   eve::wide<double> wf([](auto i, auto c)->double{ return 2*(i+c/2);});
   eve::wide<std::uint64_t> wu([](auto i, auto )->std::uint64_t{ return 2*i;});
   eve::wide x{0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
   eve::wide n{0, 1, 15, 2, 25, 26, 3, 12};

   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- n  = " << n << "\n";
   std::cout << "<- x  = " << x << "\n";

   std::cout << "-> sph_bessel_yn(wu, wf)                = " << eve::sph_bessel_yn(wu, wf) << "\n";
   std::cout << "-> sph_bessel_yn[ignore_last(2)](wu, wf)= " << eve::sph_bessel_yn[eve::ignore_last(2)](wu, wf) << "\n";
   std::cout << "-> sph_bessel_yn[wu != 2u](wu, wf)      = " << eve::sph_bessel_yn[wu != 2u](wu, wf) << "\n";
   std::cout << "-> sph_bessel_yn(n, x)                  = " << eve::sph_bessel_yn(n, x) << "\n";
}
