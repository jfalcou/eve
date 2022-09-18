#include <eve/module/complex.hpp>
#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

//using wide_ft = eve::wide <double, eve::fixed<4>>;
using      cft = eve::complex<double>;

int main()
{
//   wide_ft ref = { 1.0, 1.0, -1.0, 0.5};
//   wide_ft imf = { 0.0 , -1.0,  -5.0, 0.0};
//   auto z = eve::as_complex_t<wide_ft>(ref, imf);
//   std::cout
//     << "---- simd" << std::endl
//     << "<- z             = " << z << std::endl
//     << "-> erfcx(z)  = " << eve::erfcx(z) << std::endl;

  auto pr = [](double x,  double y){
    auto z = cft{x, y};
    std::cout << " z " << z << std::endl;
     auto fz =  eve::erfcx(z);
     std::cout << "fz "<< fz << std::endl;

//     std::cout << "z = " << z << "-> fad(z) = "<< fz << std::endl;
  };
  pr(1.0, 1.0);
  pr(0.5, 1.0);
  pr(10, 10);
  pr(65, 0);
  pr(0.01, 1);
  pr(1.0e-4, 2);
  pr(0.785398163397448, 0);
  pr(eve::inf(eve::as<double>()), 0);
  pr(eve::inf(eve::as<double>()),eve::nan(eve::as<double>()));

   pr(0.5, 0.0);
   std::cout << "real "<< eve::erfcx(0.5) << std::endl;

  return 0;
}
