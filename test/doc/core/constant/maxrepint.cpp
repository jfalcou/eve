#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

template<typename T>
consteval auto constexpr_maxrepint() { return eve::maxrepint(eve::as<T>{}); }

int main()
{
  std::cout << "---- simd"  << std::endl
            << "-> maxrepint(as<wide<float>>()) = " << eve::maxrepint(eve::as<eve::wide<float>>()) << std::endl
            << "-> maxrepint(as<wide<int>>())   = " << eve::maxrepint(eve::as<eve::wide<int>>()) << std::endl;
  std::cout << "---- scalar" << std::endl
            << "-> maxrepint(as<float>())       = " << std::setprecision(17) << eve::maxrepint(eve::as<float>{}) << std::endl
            << "-> maxrepint(as<int>())         = " << std::setprecision(17) << eve::maxrepint(eve::as<int>{}) << std::endl;

  std::cout << "-> constexpr maxrepint          = " << constexpr_maxrepint<float>() << std::endl;
}
