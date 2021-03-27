//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/fma.hpp>
#include <eve/constant/one.hpp>
#include <eve/concept/range.hpp>
#include <iterator>

namespace eve::detail
{

  template<value T0>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , T0 const &) noexcept
  {
    return T0(0);
  }

  template<value T0, value T1>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , T0 const &, T1 const &a) noexcept
  requires compatible_values<T0, T1>
  {
    using r_t = common_compatible_t<T0, T1>;
    return r_t(a);
  }

  template<value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , T0 const &x, T1 const &a, T2 const &b) noexcept
  requires compatible_values<T0, T1> &&compatible_values<T1, T2>
  {
    using r_t = common_compatible_t<T0, T1, T2>;
    return fma(r_t(x), a, b);
  }

  //================================================================================================
  //== N parameters (((..(a*x+b)*x+c)*x + ..)..)
  //================================================================================================

  template<value T0,
           value T1,
           value T2,
           value ...Ts>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_), T0 xx, T1 a, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, T2, Ts...>;
    auto x =  r_t(xx);
    r_t that(fma(x, a, b));
    auto next = [x](auto that, auto arg){
      return fma(x, that, arg);
    };
    ((that = next(that, args)),...);
    return that;
  }

  //================================================================================================
  //== N parameters (((..(x+b)*x+c)*x + ..)..) with unitary coef for x^n
  //================================================================================================

  template<value T0,
           value T1,
           value T2,
           value ...Ts>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_), T0 xx, eve::callable_one_, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T2, Ts...>;
    auto x =  r_t(xx);
    r_t that(x+b);
    auto next = [x](auto that, auto arg){
      return fma(x, that, arg);
    };
    ((that = next(that, args)),...);
    return that;
  }

  //================================================================================================
  //== Horner with ranges
  //================================================================================================

  template<value T0, range R>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_), T0 xx, R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    using r_t = common_compatible_t<T0, typename R::value_type>;
    auto x =  r_t(xx);
    if (r.empty()) return r_t(0);
    auto cur = std::begin(r);
    if (r.size() == 1) return r_t(*cur);
    else
    {
      auto cur = std::begin(r);
      r_t that(fma(x, *cur, *(cur+1)));
      auto step = [x](auto that, auto arg){
        return fma(x, that, arg);
      };
      for (std::advance(cur, 2); cur != std::end(r); std::advance(cur, 1))
        that = step(that, *cur);
      return that;
    }
  }
}
