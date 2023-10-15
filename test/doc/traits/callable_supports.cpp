#include "eve/conditional.hpp"
#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  // + supports give rules for decorator to use on a given callable and a default set of options
  // + eve::conditional give the ability to pass a mask as a decoration.
  struct func_t : basic_callable<func_t>, supports<func_t, conditional_option>
  {
    // Note that decoration doesn't impact signature declaration
    template<eve::integral_value T> auto call(T const&) -> T;
    EVE_CALLABLE_OBJECT(func_t, func_);
  } inline constexpr func;

  struct other_func_t : basic_callable<func_t>, supports<func_t, relative_conditional_option>
  {
    // Note that decoration doesn't impact signature declaration
    template<eve::integral_value T> auto call(T const&) -> T;
    EVE_CALLABLE_OBJECT(other_func_t, other_func_);
  } inline constexpr other_func;
};

namespace eve::detail
{
  // Decorated callable takes a eve::options as first parameter
  auto func_(EVE_REQUIRES(cpu_), eve::callable_options auto const& opts, eve::integral_value auto x)
  {
    // See RABERU documentation to check and access options inside a decorator.
    auto const mask = opts[condition_key];

    if constexpr(decltype(mask)::is_complete) return x*x;
    else                                      return eve::mul[mask](10,x);
  }

  auto other_func_(EVE_REQUIRES(cpu_), eve::callable_options auto const& opts, eve::integral_value auto x)
  {
    // See RABERU documentation to check and access options inside a decorator.
    auto const mask = opts[condition_key];

    if constexpr(decltype(mask)::is_complete) return x/10;
    else                                      return eve::mul[mask](x,x);
  }
}

template<typename Func, typename Opt>
inline constexpr bool can_be_decorated_with = requires(Func f, Opt o) { f[o]; };

int main()
{
  std::cout << eve::func(8) << "\n";
  std::cout << eve::func[false](8) << "\n";
  std::cout << eve::func(eve::wide<short>{77}) << "\n";
  std::cout << eve::func[eve::keep_between(2,6)](eve::wide<short>{77}) << "\n";

  std::cout << eve::other_func(8) << "\n";
  std::cout << eve::other_func(eve::wide<short>{77}) << "\n";
  std::cout << eve::other_func[eve::keep_between(2,6)](eve::wide<short>{77}) << "\n";

  std::cout << "Is func[bool] supported: "
            << std::boolalpha << can_be_decorated_with<eve::func_t, bool>
            << "\n";

  std::cout << "Is func[eve::keep_between] supported: "
            << std::boolalpha << can_be_decorated_with<eve::func_t, eve::keep_between>
            << "\n";

  std::cout << "Is other_func[bool] supported: "
            << std::boolalpha << can_be_decorated_with<eve::other_func_t, bool>
            << "\n";

  std::cout << "Is other_func[eve::keep_between] supported: "
            << std::boolalpha << can_be_decorated_with<eve::other_func_t, eve::keep_between>
            << "\n";
}
