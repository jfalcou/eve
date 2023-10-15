#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  struct some_pi_t : constant<some_pi_t>
  {
    template<eve::floating_value T> auto call(as<T>) const -> T;

    // A constant must provide a value() static member with two parameters:
    //  * an eve::options pack containing potential decorators passed to the constant
    //  * an eve::as instance to specify the output type
    template<typename T> static constexpr auto value(auto, eve::as<T>) { return T{3.14159216}; }

    EVE_CALLABLE_OBJECT(some_pi_t, some_pi_);
  } inline constexpr some_pi;
};

int main()
{
  std::cout << eve::some_pi(eve::as(1.0)) << "\n";
  std::cout << eve::some_pi(eve::as<eve::wide<float>>{}) << "\n";
  std::cout << eve::some_pi[eve::keep_between(1,3)](eve::as<eve::wide<float>>{}) << "\n\n";

  std::cout << "Is Pi(as<float>) supported: "
            << std::boolalpha << std::is_invocable_v<eve::some_pi_t, eve::as<float>>
            << "\n";

  std::cout << "Is Pi(float) supported: "
            << std::boolalpha << std::is_invocable_v<eve::some_pi_t, float>
            << "\n";

  std::cout << "Is Pi(as<wide<unsigned char>>) supported: "
            << std::boolalpha << std::is_invocable_v<eve::some_pi_t, eve::as<eve::wide<unsigned char>>>
            << "\n";
}
