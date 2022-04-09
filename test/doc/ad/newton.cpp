#include <eve/module/polynomial.hpp>
#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;
// using eve::value;
// using eve::decorator;

// template<decorator D,value T0,
//          value T1,
//          value T2,
//          value ...Ts>
//          EVE_FORCEINLINE constexpr
//          auto horn( D const &, T0 xx, T1 a, T2 b, Ts... args) noexcept
// {
//   using r_t = eve::common_compatible_t<T0, T1, T2, Ts...>;
//   auto x =  r_t(xx);
//   r_t that(eve::fma(x, a, b));
//   [[maybe_unused]] auto next = [&](auto that, auto arg){
//     return eve::fma(x, that, arg);
//   };
//   ((that = next(that, args)),...);
//   return that;
// }

//   template<value T0, value ...Ts>
//   EVE_FORCEINLINE constexpr auto horne(T0 x, Ts... args) noexcept
//   {
//     return eve::detail::newton_impl(eve::regular_type(), x, args...);
//   }

//   template<value T0, value ...Ts>
//   EVE_FORCEINLINE constexpr auto horne2(T0 x, Ts... args) noexcept
//   {
//     return eve::detail::newton_impl(eve::regular_type(), x, args...);
//   }

//   template<value T0, value ...Ts>
//   EVE_FORCEINLINE constexpr auto horne3(T0 x, Ts... args) noexcept
//   {
//     return horn(eve::regular_type(), x, args...);
//   }

int main()
{
  using eve::der;
  using eve::val;
  wide_ft x(0.5);


   std::array<float, 5> p = {1, 0, 0, 0, 0};
   std::array<float, 5> c = {1, 2, 3, 4, 5};
   auto zz = eve::newton(eve::var(x), p, c);
   std::cout          << "-> val(eve::newton(var(x), p, c)) " << val(zz)  << '\n';
   std::cout          << "-> der(eve::newton(var(x), p;, c)) " << der(zz)  << '\n';
   return 0;
}
