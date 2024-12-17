// revision 1
#include <eve/module/bessel.hpp>
#include <iostream>

eve::wide<double> wdf([](auto i, auto c)->double{ return 2*(i-c/2);});
eve::wide<std::uint64_t> wu([](auto i, auto )->std::uint64_t{ return 2*i;});
eve::wide wd{0.5, 1.5, 0.1, 1.0, 19.0, 0.0, 0.0, 10000.0};
eve::wide m{0.5, -1.0, 1.5, -2.0, 2.5, -2.6, 3.2, -12.0};

int main()
{
   std::cout << "<- wdf = " << wdf << "\n";
   std::cout << "<- wu = " << wu << "\n";
   std::cout << "<- m  = " << m << "\n";
   std::cout << "<- wd  = " << wd << "\n";

   std::cout << "-> bessel_k(wu, wdf)                = " << eve::bessel_k(wu, wdf) << "\n";
   std::cout << "-> bessel_k[ignore_last(2)](wu, wdf)= " << eve::bessel_k[eve::ignore_last(2)](wu, wdf) << "\n";
   std::cout << "-> bessel_k[wu != 2u](wu, wdf)      = " << eve::bessel_k[wu != 2u](wu, wdf) << "\n";
   std::cout << "-> bessel_k(m, wd)                  = " << eve::bessel_k(m, wd) << "\n";
   std::cout << "-> bessel_k[spherical](m, wd)       = " << eve::bessel_k[eve::spherical](m, wd) << "\n";
}
