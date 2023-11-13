#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  // Constant generations functions have a precise behavior so they can be defined using the
  // constant_callable scaffolding that enables this.
  // Note that constant_callable provides support for conditional out of the box.
  template<typename Options>
  struct some_pi_t : constant_callable<some_pi_t, Options>
  {
    // A constant must provide a value() static member with up to two parameters:
    //  * an eve::as instance to specify the output type
    //  * an optional eve::options containing potential decorators passed to the constant
    template<typename T>
    static EVE_FORCEINLINE T value(eve::as<T> const&) { return static_cast<T>(3.14159216); }

    // Supported function calls are still required
    template<eve::floating_value T>
    EVE_FORCEINLINE T     operator()(as<T>    v) const { return EVE_DISPATCH_CALL(v); }
    EVE_FORCEINLINE auto  operator()(as<char> v) const { return EVE_DISPATCH_CALL(v); }

    // Complete the callable interface.
    EVE_CALLABLE_OBJECT(some_pi_t, some_pi_);
  };

  inline constexpr auto some_pi = functor<some_pi_t>;
};

namespace eve::detail
{
  // Arch or type specific overload is still possible
  auto some_pi_(EVE_REQUIRES(cpu_), eve::callable_options auto const&, as<char> const&)
  {
    return 31415;
  }
}

int main()
{
  std::cout << eve::some_pi(eve::as(1.0)) << "\n";
  std::cout << eve::some_pi(eve::as('1')) << "\n";
  std::cout << eve::some_pi(eve::as<eve::wide<float>>{}) << "\n";
  std::cout << eve::some_pi[eve::keep_between(1,3)](eve::as<eve::wide<float>>{}) << "\n";
  std::cout << eve::some_pi[eve::keep_between(1,3).else_(99)](eve::as<eve::wide<float>>{}) << "\n\n";

  std::cout << "Is Pi(as<float>) supported: "
            << std::boolalpha << std::is_invocable_v<eve::tag_of<eve::some_pi>, eve::as<float>>
            << "\n";

  std::cout << "Is Pi(float) supported: "
            << std::boolalpha << std::is_invocable_v<eve::tag_of<eve::some_pi>, float>
            << "\n";

  std::cout << "Is Pi(as<wide<unsigned char>>) supported: "
            << std::boolalpha << std::is_invocable_v<eve::tag_of<eve::some_pi>, eve::as<eve::wide<unsigned char>>>
            << "\n";
}
