#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_vdt = eve::wide<eve::valder<float>, eve::fixed<4>>;
using vd_t     = eve::valder<float>;

namespace eve
{
  template < typename Z1, typename Z2 >
  EVE_FORCEINLINE auto pipo( Z1 const &aa, Z2 const & bb) noexcept
  {
    using r_t = decltype(average(aa, bb));
    r_t a(aa);
    r_t b(bb); //val(bb), der(bb)};
//     if constexpr(has_native_abi_v<T>)
//     {
//      auto ex = exponent(average(a, b));
//       auto r = nan(as(a));
//       auto null = is_eqz(a)||is_eqz(b);
//       r = if_else(null, zero, r);
//       auto infi = is_infinite(a) || is_infinite(b);
//       r = if_else(infi, add(a, b), r);
//       auto unord = is_unordered(a, b);
//       auto done = is_lez(sign(a)*sign(b)) || unord || infi;
//       a = if_else(done,  zero(as(a)), a);
//       b = if_else(done,  zero(as(a)), b);
//       a =  ldexp(a, -ex);
//       b =  ldexp(b, -ex);
      auto c = mul(200, eps(as(a)));
      while (eve::any(eve::abs(c) > mul(eps(as(a)), 2)))
      {
        auto an=average(a, b);
        auto bn=sqrt(mul(a, b));
        c=average(a, -b);
        a=an;
        b=bn;
      }
      return b; //if_else(done, r, ldexp(b, ex));
 //    }
//     else
//       return apply_over(agm, a, b);
  }
}

// namespace eve
// {
//   template <typename Z1, typename Z2> auto pipo(Z1 const & a, Z2 const & b){return eve::average(a, b); };
// }
int main()
{
//  auto pipo = []<eve::like<eve::valder> Z1, eve::like<eve::valder> Z2> (Z1 const & a, Z2 const & b){return a+b; };
//  auto pipo = []<typename Z1,  typename Z2> (Z1 const & a, Z2 const & b){return eve::average(a, b); };
  wide_ft x = {3, 4, 5, 6};
  wide_ft y = {1, 2, 3, 4};

  std::cout << "---- scalar" << '\n'
            << "<- x                                   = " << x << '\n'
            << "<- y                                   = " << y << '\n'
//            << "<- eve::pipo(x, y, z)               = " << eve::pipo(x, y) << '\n'
//            << "<> val(eve::pipo(var(x), var(y)) = " << eve::pipo(eve::var(x), eve::var(y))<< '\n'
            << "-> val(eve::pipo(var(x), y))     = " << eve::val(eve::pipo(eve::var(x), y)) << '\n'
//             << "-> der(eve::pipo(x, var(y)))     = " << eve::der(eve::pipo(x, eve::var(y))) << '\n'
    ;
  return 0;
}
