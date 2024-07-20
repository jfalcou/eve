// revision 0
#include <eve/module/bessel.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> cyl_bessel_jn(wf, 2*wf)                = " << eve::cyl_bessel_jn(wf, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_jn(wi, 2*wf)                = " << eve::cyl_bessel_jn(wi, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_jn(wu, 2*wf)                = " << eve::cyl_bessel_jn(wu, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_jn[ignore_last(2)](wf, 2*wf)= " << eve::cyl_bessel_jn[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_jn[ignore_last(2)](wi, 2*wf)= " << eve::cyl_bessel_jn[eve::ignore_last(2)](wi, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_jn[ignore_last(2)](wu, 2*wf)= " << eve::cyl_bessel_jn[eve::ignore_last(2)](wu, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_jn[wf != -2.0f](wf, 2*wf)   = " << eve::cyl_bessel_jn[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_jn[wi != -2](wi, 2*wf)      = " << eve::cyl_bessel_jn[wi != -2](wi, 2*wf) << "\n";
   std::cout << "-> cyl_bessel_jn[wu != 2u](wu, 2*wf)      = " << eve::cyl_bessel_jn[wu != 2u](wu, 2*wf) << "\n";
}
