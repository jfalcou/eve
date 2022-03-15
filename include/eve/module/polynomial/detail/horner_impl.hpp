//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/range.hpp>
#include <concepts>
#include <iterator>
#include <initializer_list>

namespace eve::detail
{
  //================================================================================================
  //== N+ 1  parameters (((..(a*x+b)*x+c)*x + ..)..)
  //================================================================================================
  //==  N = 0
  template<decorator D,  value T0>
  EVE_FORCEINLINE constexpr auto horner_impl(D const &, T0 const &) noexcept
  {
    return T0(0);
  }

  //==  N = 1
  template<decorator D, value T0, value T1>
  EVE_FORCEINLINE constexpr auto horner_impl(D const &
                                            , T0 const &, T1 const &a) noexcept
  requires compatible_values<T0, T1>
  {
    using r_t = common_compatible_t<T0, T1>;
    return r_t(a);
  }

  //==  N = 2
  template<decorator D, value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto horner_impl(D const &
                                            , T0 const &x, T1 const &a, T2 const &b) noexcept
  requires compatible_values<T0, T1> &&compatible_values<T1, T2>
  {
    using r_t = common_compatible_t<T0, T1, T2>;
    return D()(fma)(r_t(x), a, b);
  }

  //==  N >= 3
  template<decorator D,
           value T0,
           value T1,
           value T2,
           value ...Ts>
  EVE_FORCEINLINE constexpr
  auto horner_impl(D const & d
                  , T0 xx, T1 a, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, T2, Ts...>;
    auto x =  r_t(xx);
    auto dfma = d(fma);
    r_t that(dfma(x, a, b));
    [[maybe_unused]] auto next = [&](auto that, auto arg){
      return dfma(x, that, arg);
    };
    ((that = next(that, args)),...);
    return that;
  }

  //================================================================================================
  //== N+ 1  parameters (((..(x+b)*x+c)*x + ..)..) with unitary leader coefficients
  //================================================================================================
  //==  N = 0,nope one is there
  //==  N = 1
  template<decorator D, value T0>
  EVE_FORCEINLINE constexpr auto horner_impl(D const &
                                            , T0 const & x, callable_one_ const &) noexcept
  {
    return one(as(x));
  }
  //==  N = 2
  template<decorator D, value T0, value T2>
  EVE_FORCEINLINE constexpr auto horner_impl(D const &
                                            , T0 const &x, callable_one_ const &, T2 const &b) noexcept
  requires compatible_values<T0, T2>
  {
    return add(x, b);
  }

  //==  N >= 3
  template<decorator D,
           value T0,
           value T2,
           value ...Ts>
  EVE_FORCEINLINE constexpr
  auto horner_impl(D const & d
                  , T0 xx, callable_one_ const&, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T2, Ts...>;
    auto x =  r_t(xx);
    auto dfma = d(fma);
    r_t that(add(x, b));
    auto next = [&](auto that, auto arg){
      return dfma(x, that, arg);
    };
    ((that = next(that, args)),...);
    return that;
  }

  //================================================================================================
  //== Horner with iterators
  //================================================================================================
  template<decorator D, value T0, std::input_iterator IT>
  EVE_FORCEINLINE constexpr auto horner_impl( D const & d
                                            , T0 xx
                                            , IT const & first
                                            , IT const & last
                                            ) noexcept
  requires (compatible_values<T0, typename std::iterator_traits<IT>::value_type>)
  {
    using r_t = common_compatible_t<T0, typename std::iterator_traits<IT>::value_type>;
    auto x =  r_t(xx);
    if (first == last) return r_t(0);
    if (std::distance(first, last) == 1) return r_t(*first);
    else
    {
      using std::advance;
      auto cur = first;
      advance(cur, 1);
      auto dfma = d(fma);
      r_t that(dfma(x, *first, *cur));
      auto step = [&](auto that, auto arg){
        return dfma(x, that, arg);
      };
      for (advance(cur, 1); cur != last; advance(cur, 1))
        that = step(that, *cur);
      return that;
    }
  }

  //================================================================================================
  //== Horner with iterators and unitary leader coefficient
  //================================================================================================
  template<decorator D, value T0, std::input_iterator IT>
  EVE_FORCEINLINE constexpr auto horner_impl( D const & d
                                            , T0 xx
                                           ,  callable_one_ const &
                                            , IT const & first
                                            , IT const & last
                                            ) noexcept
  requires (compatible_values<T0, typename std::iterator_traits<IT>::value_type>)
  {
    using r_t = common_compatible_t<T0, typename std::iterator_traits<IT>::value_type>;
    auto x =  r_t(xx);
    if(first == last) return one(as(x));
    auto cur = first;
    auto dfma = d(fma);
    r_t that(add(x, *cur));
    auto step = [&](auto that, auto arg){
      return dfma(x, that, arg);
    };
    using std::advance;
    for (advance(cur, 1); cur != last; advance(cur, 1))
      that = step(that, *cur);
    return that;
  }

  //================================================================================================
  //== Horner with ranges
  //================================================================================================
  template<decorator D, value T0, range R>
  EVE_FORCEINLINE constexpr auto horner_impl(D const & d
                                        , T0 xx, R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    return horner_impl(d, xx, std::begin(r), std::end(r));
  }

  //================================================================================================
  //== Horner with ranges and leading unitary coefficient
  //================================================================================================
  template<decorator D, value T0, range R>
  EVE_FORCEINLINE constexpr auto horner_impl(D const & d
                                            , T0 xx
                                            , callable_one_ const &
                                            , R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    return horner_impl(d, xx, one, std::begin(r), std::end(r));
  }
}
