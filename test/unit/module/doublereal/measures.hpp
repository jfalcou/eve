//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/doublereal.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
namespace bm =  boost::multiprecision;
using bm110 = bm::number<bm::backends::cpp_bin_float<165, bm::backends::digit_base_2, void, std::int16_t, -1022, 1023>, bm::et_off>;
using bm46  = bm::number<bm::backends::cpp_bin_float<46 , bm::backends::digit_base_2, void, std::int16_t, -126, 127>, bm::et_off>;

namespace tts
{
  template<eve::ordered_value Z>
  EVE_FORCEINLINE  auto to_bm110( Z const& z) noexcept
  requires(eve::is_doublereal_v<Z>)
  {
    auto [h, l] = z;
    return  bm110(h)+bm110(l);
  }

  template<typename T>
  auto uptype(T const & z)
  {
    if constexpr(sizeof(T) == 4) return eve::to_double(z);
    else return to_bm110(z);
  }

  template < typename T, typename BM>
  auto  to_doublereal(BM t)
    requires (eve::scalar_value<T>)
  {
    using u_t = eve::underlying_type_t<T>;
    u_t h(t);
    auto self = eve::two_add(h, u_t(t-BM(h)));
    return eve::make_doublereal(self);
  }

  template<typename T>
  double ulp_distance(T const & l, T const & r) requires( eve::is_doublereal_v<T> )
  {
   return eve::maximum(eve::high(eve::ulpdist(l,r)));
  }

  template<typename T, typename N>
  double ulp_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r)
  requires( eve::is_doublereal_v<T> )
  {
   return eve::maximum(eve::high(eve::ulpdist(l,r)));
  }

  template<typename T> double relative_distance(T const &a, T const &b) requires(eve::is_doublereal_v<T>)
  {
    if((a == b) || (eve::is_nan(a) && eve::is_nan(b))) return 0.;
    if(eve::is_infinite(a) || eve::is_infinite(b) || eve::is_nan(a) || eve::is_nan(b))
      return std::numeric_limits<double>::infinity();
    return eve::high(100. * (eve::abs(a - b) / eve::max(eve::one(eve::as(a)), eve::max(eve::abs(a), eve::abs(b)))));
  }

  template<typename T, typename N>
  auto relative_distance(eve::wide<T,N> const &a, eve::wide<T,N> const &b) requires(eve::is_doublereal_v<T>)
  {
    auto r = eve::if_else(((a == b) || (eve::is_nan(a) && eve::is_nan(b))),
                     eve::zero,
                     eve::if_else((eve::is_infinite(a) || eve::is_infinite(b) || eve::is_nan(a) || eve::is_nan(b))
                            ,  eve::inf(eve::as(a)),
                             100. * (eve::abs(a - b) / eve::max(eve::one(eve::as(a)), eve::max(eve::abs(a), eve::abs(b))))
                            )
                    );
    return double(eve::maximum(eve::high(r)));
  }

  template<typename T> auto absolute_distance(T const &l, T const &r) requires(eve::is_doublereal_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }

  template<typename T, typename N>
  auto absolute_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_doublereal_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }
}
