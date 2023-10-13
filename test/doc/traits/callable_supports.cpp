#include <iostream>
#include <type_traits>
#include <eve/traits/overload.hpp>
#include <eve/wide.hpp>

namespace eve
{
  // + supports give rules for decorator to use on a given callable and a default set of options
  // + eve::conditional give the ability to pass a mask as a decoration.
  struct func_t : supports<func_t, conditional>
  {
    // Note that decoration doesn't impact signature declaration
    template<eve::integral_value T> auto call(T const&) -> T;
    EVE_CALLABLE_OBJECT(func_t, func_);
  } inline constexpr func;
};

namespace eve::detail
{
  // Decorated callable takes a eve::options as first parameter
  template<typename D>
  auto func_(EVE_REQUIRES(cpu_), eve::options<D> opts, eve::integral_value auto x)
  {
    // See RABERU documentation to check and access options inside a decorator.
    auto const mask = opts[option::condition];

    if constexpr(decltype(mask)::is_complete) return x*x;
    else                                      return eve::mul[mask](10,x);
  }
}

int main()
{
  std::cout << eve::func(8) << "\n";
  std::cout << eve::func[false](8) << "\n";
  std::cout << eve::func(eve::wide<short>{77}) << "\n";
  std::cout << eve::func[eve::keep_between(2,6)](eve::wide<short>{77}) << "\n";
}
