#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  struct func_t : basic_callable<func_t>
  {
    // Supported signatures
    template<eve::integral_value T> auto call(T const&) -> T;
                                    auto call(double)   -> double;
                                    auto call(float)    =  delete;

    // Register this callable type to EVE overload system
    EVE_CALLABLE_OBJECT(func_t, func_);
  } inline constexpr func;
};

// As func_t used EVE_CALLABLE_OBJECT, we should write overloads in eve::detail
namespace eve::detail
{
  auto func_(EVE_REQUIRES(cpu_), eve::callable_options auto const&, eve::integral_value auto x) {  return x*x;  }
  auto func_(EVE_REQUIRES(cpu_), eve::callable_options auto const&, double x)                   {  return 1./x; }
}

int main()
{
  std::cout << eve::func(8) << "\n";
  std::cout << eve::func(eve::wide<short>{77}) << "\n";
  std::cout << eve::func(25.) << "\n";

  std::cout << "Is func(float) supported: "
            << std::boolalpha << std::is_invocable_v<eve::func_t, float>
            << "\n";

  std::cout << "Is func(wide<float>) supported: "
            << std::boolalpha << std::is_invocable_v<eve::func_t, eve::wide<float>>
            << "\n";
}
