#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  struct pi_t : constant<pi_t>
  {
    template<eve::floating_value T> auto call(as<T>) const -> T;

    // A constant must provide a value() static member with two parameters:
    //  * an eve::options pack containing potential decorators passed to the constant
    //  * an eve::as instance to specify the output type
    template<typename T> static constexpr auto value(auto, eve::as<T>) { return T{3.14159216}; }

    EVE_CALLABLE_OBJECT(pi_t, pi_);
  } inline constexpr Pi;
};

int main()
{
  std::cout << eve::Pi(eve::as(1.0)) << "\n";
  std::cout << eve::Pi(eve::as<eve::wide<float>>{}) << "\n";
  std::cout << eve::Pi[eve::keep_between(1,3)](eve::as<eve::wide<float>>{}) << "\n\n";


  std::cout << "Pi(int)                 does not compile: "
            << std::boolalpha << !std::is_invocable_v<eve::pi_t, float>
            << "\n";

  std::cout << "Pi(wide<unsigned char>) does not compile: "
            << std::boolalpha << !std::is_invocable_v<eve::pi_t, eve::wide<unsigned char>>
            << "\n";
}
