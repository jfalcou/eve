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
  auto [a, b, c] = eve::to_euler(q, eve::_Z,  eve::_Y,  eve::_X, eve::Extrinsic);
  std::cout
    << "---- simd" << std::endl
    << "<- q              = " << q << std::endl
    << "   auto [a, b, c] = eve::to_euler(q, eve::_Z,  eve::_Y,  eve::_X);" << std::endl
    << "<- v              = " << "{" << v[0] << ", " << v[1] << ", " << v[2] << "}" << std::endl
    << " -> {a, b, c]     = " << "{" << a    << ", " << b  << ", " << c << "}" << std::endl;
  return 0;
}
