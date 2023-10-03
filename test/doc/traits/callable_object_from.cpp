#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

// Register my_lib::impl as a proper callable namespace
namespace my_lib::impl { EVE_CALLABLE_NAMESPACE(); }

// EVE_CALLABLE_OBJECT_FROM helps defining your own EVE-like callable in your own library
namespace my_lib
{
  struct func_t
  {
    // Supported signatures
    template<eve::integral_value T> auto call(T const&) -> T;
                                    auto call(double)   -> double;
                                    auto call(float)    =  delete;

    // Register this callable type to EVE overload system
    EVE_CALLABLE_OBJECT_FROM(my_lib::impl, func_t, func_);
  } inline constexpr func;

  // As func_t used EVE_CALLABLE_OBJECT_FROM, we can write overloads in this namespace
  namespace impl
  {
    auto func_(EVE_REQUIRES(eve::cpu_), eve::integral_value auto x) {  return x*x;  }
    auto func_(EVE_REQUIRES(eve::cpu_), double x)                   {  return 1./x; }
  }
}

int main()
{
  std::cout << my_lib::func(8) << "\n";
  std::cout << my_lib::func(eve::wide<short>{77}) << "\n";
  std::cout << my_lib::func(25.) << "\n";

  std::cout << "func(float)       does not compile: "
            << std::boolalpha << !std::is_invocable_v<my_lib::func_t, float>
            << "\n";

  std::cout << "func(wide<float>) does not compile: "
            << std::boolalpha << !std::is_invocable_v<my_lib::func_t, eve::wide<float>>
            << "\n";
}
