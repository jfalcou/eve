//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/wide.hpp>
#include <eve/detail/top_bits.hpp>
#include <eve/function/all.hpp>

namespace eve
{
  template<typename T, typename N>
  inline bool compare_equal(wide<T, N> const &l, wide<T, N> const &r)
  {
    return eve::all(l == r);
  }

  template<typename T>
  inline bool compare_equal(logical<T> const &l, logical<T> const &r)
  {
    if constexpr(eve::simd_value<T>)  return l.bitmap() == r.bitmap();
    else                              return l == r;
  }

  template<typename T>
  inline std::string to_string(logical<T> const &l)
  {
    std::ostringstream str;
    str << l;
    return str.str();
  }

  template<typename T>
  inline std::string to_string(detail::top_bits<T> const &l)
  {
    std::ostringstream str;
    str << l;
    return str.str();
  }
}

namespace tts
{
  template<typename T, typename N>
  inline double ulp_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, tts::ulp_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T>
  inline double ulp_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : std::numeric_limits<double>::infinity();
  }

  template<typename T, typename N>
  inline double relative_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, tts::relative_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T>
  inline double relative_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : 1;
  }

  template<typename T, typename N>
  inline double absolute_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, tts::absolute_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T>
  inline double absolute_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : 1;
  }
}
