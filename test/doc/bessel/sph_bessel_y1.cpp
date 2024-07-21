// revision 1
#include <eve/module/bessel.hpp>
#include <iostream>

eve::wide<double> wf0([](auto i, auto c)->double{ return 2*(i+c/2);});
eve::wide         wf1{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};

int main()
{
   std::cout << "<- wf0 = " << wf0 << "\n";
   std::cout << "<- wf1 = " << wf1 << "\n";

   std::cout << "-> sph_bessel_y1(wf0)                = " << eve::sph_bessel_y1(wf0) << "\n";
   std::cout << "-> sph_bessel_y1[ignore_last(2)](wf0)= " << eve::sph_bessel_y1[eve::ignore_last(2)](wf0) << "\n";
   std::cout << "-> sph_bessel_y1[wf0!= 6.0](wf0)     = " << eve::sph_bessel_y1[wf0!= 6.0f](wf0) << "\n";
   std::cout << "-> sph_bessel_y1(wf1)                = " << eve::sph_bessel_y1(wf1) << "\n";
}
