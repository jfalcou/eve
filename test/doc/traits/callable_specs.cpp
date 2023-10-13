#include "eve/detail/raberu.hpp"
#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  // Defines two RABERU flags
  using namespace rbr::literals;
  inline constexpr auto precise = "precise"_fl;
  inline constexpr auto scale   = "scale"_fl;

  // Defines a support specification
  struct precision
  {
    auto process_option(auto const& base, rbr::concepts::exactly<precise> auto opt) const
    {
      return options{rbr::merge(options{opt}, base)};
    }

    auto process_option(auto const& base, rbr::concepts::exactly<scale> auto opt) const
    {
      return options{rbr::merge(options{opt}, base)};
    }

    EVE_FORCEINLINE static constexpr auto defaults() noexcept { return options{};  }
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
  auto func_(EVE_REQUIRES(cpu_), eve::options<D> const& opt, int x)
  {
    // We retrieve the option's value via the RABERU settings interface
    return  x * (opt[scale] ? 10. : 1.)
              + (opt[precise] ? 3.14159 : 3.14);
  }
}

int main()
{
  std::cout << eve::func(1)                 << "\n";
  std::cout << eve::func[eve::precise](1)        << "\n";
  std::cout << eve::func[eve::scale](1)          << "\n";
  std::cout << eve::func[eve::scale][eve::precise](1) << "\n";
  std::cout << eve::func[eve::precise][eve::scale](1) << "\n";
}
