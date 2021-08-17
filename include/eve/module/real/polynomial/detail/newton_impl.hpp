//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_compatible.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/decorator.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/one.hpp>
#include <eve/concept/range.hpp>

#include <concepts>
#include <iterator>
#include <initializer_list>

namespace eve::detail
{
  //================================================================================================
  //== Newton with iterators
  //================================================================================================
  template<decorator D, value T0, std::input_iterator IT1
                                , std::input_iterator IT2>
  EVE_FORCEINLINE constexpr auto newton_impl( D const & d
                                            , T0 xx
                                            , IT1 const & firstc
                                            , IT1 const & lastc
                                            , IT2 const & firstn
                                             ) noexcept
  requires (compatible_values<T0, typename std::iterator_traits<IT1>::value_type> &&
            compatible_values<T0, typename std::iterator_traits<IT2>::value_type>)

  {
    using r_t = common_compatible_t<T0, typename std::iterator_traits<IT1>::value_type
                                      , typename std::iterator_traits<IT2>::value_type>;
    auto x =  r_t(xx);
    if (firstc == lastc) return r_t(0);
    if (std::distance(firstc, lastc) == 1) return r_t(*firstc);
    else
    {
      using std::advance;
      auto curc = firstc;
      auto curn = firstn;
      advance(curc, 1);
      advance(curn, 1);
      auto dfma = d(fma);
      r_t that(dfma(sub(x, *firstn), *firstc, *curc));
      auto step = [&](auto that, auto argc, auto argn){
        return dfma(sub(x, argn), that, argc);
      };
      for (advance(curc, 1); curc != lastc; advance(curc, 1), advance(curn, 1))
        that = step(that, *curc, *curn);
      return that;
    }
  }

  //================================================================================================
  //== Newton with ranges
  //================================================================================================
  template<decorator D, value T0, range R1, range R2>
  EVE_FORCEINLINE constexpr auto newton_impl(D const & d
                                        , T0 xx, R1 const & rc, R2 rn) noexcept
  requires (compatible_values<T0, typename R1::value_type>
            && compatible_values<T0, typename R2::value_type>
            && (!simd_value<R1>)
            && (!simd_value<R2>))
  {
    return newton_impl(d, xx, std::begin(rc), std::end(rc), std::begin(rn));
  }
}
