#include <eve/module/quaternion.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <array>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft r = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft i = { 2.0f , -1.0,  -5.0, 0.0};
  wide_ft j = { 4.0f, 0.0f, -1.0f, -0.5f};
  wide_ft k = { -2.0f , 1.0,  3.0, 10.0};
  auto q = eve::as_quaternion_t<wide_ft>(r, i, j, k);
  std::array<float, 3> v{1, 2, 3};
  auto res = eve::rot_vec(q, std::span(v));
  std::cout
    << "---- simd" << std::endl
    << "<- q              = " << q << std::endl
    << "<- v              = " << "{" << v[0] << ", " << v[1] << ", " << v[2] << "}" << std::endl
    << "-> rot_vec(q, v)  = " << "{" << res[0] << ", " << res[1] << ", " << res[2] << "}" << std::endl;
  return 0;
}
