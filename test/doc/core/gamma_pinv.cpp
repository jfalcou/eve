#include <eve/function/gamma_pinv.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
//   wide_ft k = {1.0e-3f, 0.1f, 0.75f, 0.5f};
//   wide_ft p = {0.0,  0.3, 0.7, 1.0};
//   wide_ft phi1 = phi0+eve::pio_2(as(phi0));

//   std::cout << "---- simd" << '\n'
//              << "<- phi0                   = " << phi0 << '\n'
//              << "<- phi1                   = " << phi1 << '\n'
//              << "<- k                      = " << k << '\n'
//              << "-> gamma_pinv(p, k) = " << eve::gamma_pinv(phi0, k) << '\n';

//   float kf = 0.1f;
//   float pf = 1.1f;

//   std::cout << "---- scalar" << '\n'
//             << "<- xf                      = " << kf << '\n'
//             << "<- phif                    = " << phif<< '\n'
//             << "-> gamma_pinv(pf, kf) = " << eve::gamma_pinv(phif, kf) << '\n';


 for(double kf= 1.0f; kf < 100.0f; kf+= 10.0f)
 {
   for(double i=0.99999f; i > 0.0001f; i*= 0.9f)
   {
     std::cout <<  "eve::gamma_pinv(" << i << ", " << kf << ") "<<  eve::gamma_pinv(i, kf) << std::endl;
   }
 }
 return 0;
}
