// revision 0
#include <eve/module/bessel.hpp>
#include <iostream> 
 
eve::wide<double> wf([](auto i, auto c)->double{ return 2*(i-c/2);});
eve::wide<std::int64_t> wi([](auto i, auto c)->std::int64_t{ return i-c/2;});
eve::wide<std::uint64_t> wu([](auto i, auto )->std::uint64_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> cyl_bessel_kn(wf, 2*wf)                = " << eve::cyl_bessel_kn(wf, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_kn(wi, 2*wf)                = " << eve::cyl_bessel_kn(wi, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_kn(wu, 2*wf)                = " << eve::cyl_bessel_kn(wu, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_kn[ignore_last(2)](wf, 2*wf)= " << eve::cyl_bessel_kn[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_kn[ignore_last(2)](wi, 2*wf)= " << eve::cyl_bessel_kn[eve::ignore_last(2)](wi, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_kn[ignore_last(2)](wu, 2*wf)= " << eve::cyl_bessel_kn[eve::ignore_last(2)](wu, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_kn[wf != -2.0f](wf, 2*wf)   = " << eve::cyl_bessel_kn[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_kn[wi != -2](wi, 2*wf)      = " << eve::cyl_bessel_kn[wi != -2](wi, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_kn[wu != 2u](wu, 2*wf)      = " << eve::cyl_bessel_kn[wu != 2u](wu, 2*wf) << "\n";
}
