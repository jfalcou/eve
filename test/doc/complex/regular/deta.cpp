#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft ref1 = { 3.0f, 2.0f, 1.0f, 0.6f};
  wide_ft imf1 = { 2.0f , -1.0,  -5.0, 0.0};
  auto zc = eve::as_complex_t<wide_ft>(ref1, imf1);
  auto z = eve::as_complex_t<double>(1.0, 0.0);
  auto zf= eve::as_complex_t<float >(1.0, 0.0);
  std::cout
    << "---- simd" << std::endl
    << "<- z           = " << z << std::endl
    << "-> deta(1, z)  = " << eve::deta(1u, z) << std::endl
    << "-> deta(2, z)  = " << eve::deta(2u, z) << std::endl
    << "-> deta(3, z)  = " << eve::deta(3u, z) << std::endl
    << "-> deta(2, 0.2)= " << eve::deta(2u, 0.2)<< std::endl
    << "-> deta(1, 0.2)= " << eve::deta(1u, 0.2)<< std::endl
    << "-> deta(1, z)  = " << eve::deta(1u, zf) << std::endl
    << "-> deta(2, z)  = " << eve::deta(2u, zf) << std::endl
    << "-> deta(3, z)  = " << eve::deta(3u, zf) << std::endl
    << "-> deta(2, 0.2)= " << eve::deta(2u, 0.2f)<< std::endl
    << "-> deta(1, 0.2)= " << eve::deta(1u, 0.2f)<< std::endl
    << "<- zc          = " << zc << std::endl
    << "-> deta(1, zc) = " << eve::deta(1u, zc)<< std::endl;
  return 0;
}
