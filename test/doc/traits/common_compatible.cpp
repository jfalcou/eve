#include <iostream>
#include <eve/traits/common_compatible.hpp>
#include <eve/wide.hpp>

int main()
{
  using float_type      = eve::common_compatible<float,float,float>::type;
  using wide_float_type = eve::common_compatible<eve::wide<float>,eve::wide<float>>::type;
  using mixed_type      = eve::common_compatible<int, eve::wide<float>, double>::type;

  std::cout << std::boolalpha
            << std::is_same<float_type, float>::value                 << "\n"
            << std::is_same<wide_float_type, eve::wide<float>>::value << "\n"
            << std::is_same<mixed_type, eve::wide<float>>::value      << "\n";
}
