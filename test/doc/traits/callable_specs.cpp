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
    template<eve::any_options_from<precise, scale> O>
    auto process(auto const& base, O const& opt) const
    {
      auto new_opts = rbr::merge(options{opt}, base);
      return options<decltype(new_opts)>{new_opts};
    }

    constexpr auto default_to(auto const& base) const noexcept { return base; }
  };

  // Make this callable supports the precision options
  template<typename Options>
  struct func_t : callable<func_t, Options, precision>
  {
    double operator()(int v) const
    {
      return this->behavior(as<double>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(func_t, func_);
  };

  // Build the callable object from the function object type
  inline constexpr auto func = functor<func_t>;
};

namespace eve::detail
{
  auto func_(EVE_REQUIRES(cpu_), eve::callable_options auto const& opt, int x)
  {
    // We retrieve the option's value via the RABERU settings interface
    return  x * (opt[scale] ? 10. : 1.)
              + (opt[precise] ? 3.1416 : 3.2);
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
