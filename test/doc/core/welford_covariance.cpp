// revision 0
// revision 0
#include <eve/module/core.hpp>
#include "../../vec3.hpp"
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  // scalar welford_covariance vec3<float>
  vec3<float> a(1.0, 2.0, 3.0);
  vec3<float> b(-3.0, -4.0, -6.0);
  std::cout <<  "a " << a << std::endl;
  std::cout <<  "b " << b << std::endl;
  std::cout << "eve::welford_covariance[eve::unbiased](a, b) = "<< eve::welford_covariance[eve::unbiased](a, b) << std::endl;
  std::cout << "eve::welford_covariance[eve::unbiased](a, a) = " << eve::welford_covariance[eve::unbiased](a, a) << std::endl;
  std::cout << "eve::welford_covariance[eve::unbiased](b, a) = " << eve::welford_covariance[eve::unbiased](b, a) << std::endl;
  std::cout << "eve::welford_covariance[eve::unbiased](b, b) = " << eve::welford_covariance[eve::unbiased](b, b) << std::endl;

  // simd welford_covariance eve::wide<vec3<float>, eve::fixed<4>>;
  using wv3_t = eve::wide<vec3<float>, eve::fixed<4>>;
  auto wa = wv3_t(a, a, b, b);
  auto wb = wv3_t(b, a, a, b);
   std::cout << "wa " << wa << std::endl;
   std::cout << "wb " << wb << std::endl;
   std::cout << "eve::welford_covariance[eve::widen][eve::unbiased](wa, wb) = "<< eve::welford_covariance[eve::widen][eve::unbiased](wa, wb) << std::endl;


  kumi::tuple x{4.0f, 3.0f, 2.0f, 1.0f};
  kumi::tuple y{1.0f, 2.0f, 3.0f, 4.0f};
  std::cout << eve::welford_covariance[eve::unbiased](x, x) <<  std::endl;
  std::cout << eve::welford_covariance[eve::unbiased](x, y) <<  std::endl;
  std::cout << eve::welford_covariance[eve::unbiased](y, x) <<  std::endl;

}
