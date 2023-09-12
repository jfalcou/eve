#include "eve/detail/raberu.hpp"
#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  namespace option
  {
    // Defines two RABERU flags
    using namespace rbr::literals;
    inline constexpr auto precise = "precise"_fl;
    inline constexpr auto scale   = "scale"_kw;
  }

  // Defines a support specification
  struct precision
  {
    auto operator[](rbr::concepts::exactly<option::precise> auto const&) -> void;
    auto operator[](rbr::concepts::exactly<option::scale>   auto const&) -> void;
    EVE_FORCEINLINE static constexpr auto defaults() noexcept { return options{option::scale = 1.};  }
  };

  // Make this callable supports the precision options
  struct func_t : supports<func_t, precision>
  {
    auto call(int) -> double;
    EVE_CALLABLE_OBJECT(func_t, func_);
  } inline constexpr func;
};

namespace eve::detail
{
  template<typename D>
  auto func_(EVE_EXPECTS(cpu_), eve::options<D> const& opt, int x)
  {
    // We retrieve the option's value via the RABERU settings interface
    return x * opt[option::scale] * (opt[option::precise] ? 3.14159 : 3.14);
  }
}

int main()
{
  using namespace eve::option;
  std::cout << eve::func(1)                         << "\n";
  std::cout << eve::func[precise](1)                << "\n";
  std::cout << eve::func[scale = -.1](1)            << "\n";
  std::cout << eve::func[scale = 10.][precise](1)   << "\n";
  std::cout << eve::func[precise][scale = -1.5](1)  << "\n";
}
