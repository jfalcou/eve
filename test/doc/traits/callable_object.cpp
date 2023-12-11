#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  template<typename Options>
  struct func_t : callable<func_t, Options>
  {
    // operator() are defined here to maximize quality of error message. They all use EVE_DISPATCH_CALL at some point.
    template<eve::integral_value T>
    EVE_FORCEINLINE T       operator()(T v)       const { return EVE_DISPATCH_CALL(v); }
    EVE_FORCEINLINE double  operator()(double v)  const { return EVE_DISPATCH_CALL(v); }
    EVE_FORCEINLINE void    operator()(float)     const = delete;

    // This ties the function object to the overload set
    EVE_CALLABLE_OBJECT(func_t, func_);
  };

  // Build the callable object from the function object type
  inline constexpr auto func = functor<func_t>;
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

  std::cout << "Is func(double) supported     : "
            << std::boolalpha << std::is_invocable_v<eve::tag_t<eve::func>, double>
            << "\n";

  std::cout << "Is func(float) supported      : "
            << std::boolalpha << std::is_invocable_v<eve::tag_t<eve::func>, float>
            << "\n";

  std::cout << "Is func(wide<float>) supported: "
            << std::boolalpha << std::is_invocable_v<eve::tag_t<eve::func>, eve::wide<float>>
            << "\n";
}
