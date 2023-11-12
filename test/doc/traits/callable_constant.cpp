#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  template<typename Options>
  struct some_pi_t : constant_callable<some_pi_t, Options>
  {
    // A constant must provide a value() static member with two parameters:
    //  * an eve::options pack containing potential decorators passed to the constant
    //  * an eve::as instance to specify the output type
    template<typename T>
    static EVE_FORCEINLINE T value(eve::as<T> const&) { return static_cast<T>(3.14159216); }

    // Supported function calls
    template<eve::floating_value T>
    EVE_FORCEINLINE T operator()(as<T> v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(some_pi_t, some_pi_);
  };

  inline constexpr auto some_pi = functor<some_pi_t>;
};

int main()
{
  std::cout << eve::some_pi(eve::as(1.0)) << "\n";
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
