#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

// Register my_lib::impl as a proper callable namespace
namespace my_lib::impl { EVE_CALLABLE_NAMESPACE(); }

// EVE_CALLABLE_OBJECT_FROM helps defining your own EVE-like callable in your own library
namespace my_lib
{
  template<typename Options>
  struct func_t : eve::callable<func_t, Options>
  {
    // operator() are defined here to maximize quality of error message. They all use EVE_DISPATCH_CALL at some point.
    template<eve::integral_value T>
    EVE_FORCEINLINE T       operator()(T v)       const { return EVE_DISPATCH_CALL(v); }
    EVE_FORCEINLINE double  operator()(double v)  const { return EVE_DISPATCH_CALL(v); }
    EVE_FORCEINLINE void    operator()(float)     const = delete;

    // This ties the function object to the overload set
    EVE_CALLABLE_OBJECT_FROM(my_lib::impl, func_t, func_);
  };

  // Build the callable object from the function object type
  inline constexpr auto func = eve::functor<func_t>;

  // As func_t used EVE_CALLABLE_OBJECT_FROM, we can write overloads in this namespace
  namespace impl
  {
    auto func_(EVE_REQUIRES(eve::cpu_), eve::callable_options auto const&, eve::integral_value auto x) {  return x*x;  }
    auto func_(EVE_REQUIRES(eve::cpu_), eve::callable_options auto const&, double x)                   {  return 1./x; }
  }
}

int main()
{
  std::cout << my_lib::func(8) << "\n";
  std::cout << my_lib::func(eve::wide<short>{77}) << "\n";
  std::cout << my_lib::func(25.) << "\n";

  std::cout << "Is func(double) supported     : "
            << std::boolalpha << std::is_invocable_v<eve::tag_of<my_lib::func>, double>
            << "\n";

  std::cout << "Is func(float) supported      : "
            << std::boolalpha << std::is_invocable_v<eve::tag_of<my_lib::func>, float>
            << "\n";

  std::cout << "Is func(wide<float>) supported: "
            << std::boolalpha << std::is_invocable_v<eve::tag_of<my_lib::func>, eve::wide<float>>
            << "\n";
}
