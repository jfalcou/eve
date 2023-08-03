#include <eve/module/quaternion.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft a = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft b = { 2.0f , -1.0,  -5.0, 0.0};
  wide_ft c = { 1.0f, -3.0f,  -4.0f, 1.5f};
  wide_ft d = { -2.0, 1.5f, 2.3f, 6.7f};
  wide_ft r1= { 1.0f, 2.0f, 3.0f,  0.0f};
  wide_ft r2= { 0.0f, 3.0f, 4.0f, 10.0f};

  std::cout
    << "---- simd" << std::endl
    << "<- a                               = " << a << std::endl
    << "<- b                               = " << b << std::endl
    << "<- c                               = " << c << std::endl
    << "<- d                               = " << d << std::endl
    << "<- r1                              = " << c << std::endl
    << "<- r2                              = " << d << std::endl
    << "-> cylindrical(r1, b, c, d)        = " << eve::from_cylindrical(r1, b, c, d) << std::endl
    << "-> cylindrospherical(r1, r2, c, d) = " << eve::from_cylindrospherical(r1, r2, c, d) << std::endl
    << "-> multipolar(r1, c, r2, d)        = " << eve::from_multipolar(r1, c, r2, d) << std::endl
    << "-> semipolar(r1, b, c, d)          = " << eve::from_semipolar(r1, b, c, d) << std::endl
    << "-> spherical(r1, b, c, d)          = " << eve::from_spherical(r1, b, c, d) << std::endl
   ;

  return 0;
}
