//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/traits/common_compatible.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/add.hpp>
#include <eve/function/horner.hpp>
#include <eve/function/pedantic/horner.hpp>
#include <eve/function/numeric/horner.hpp>
#include <eve/function/decorator.hpp>
#include <eve/function/fma.hpp>
#include <eve/constant/one.hpp>
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
  EVE_FORCEINLINE constexpr auto reverse_horner_impl(D const &, T0 const &) noexcept
  {
    return T0(0);
  }

  //==  N = 1
  template<decorator D, value T0, value T1>
  EVE_FORCEINLINE constexpr auto reverse_horner_impl(D const &
                                            , T0 const &, T1 const &a) noexcept
  requires compatible_values<T0, T1>
  {
    using r_t = common_compatible_t<T0, T1>;
    return r_t(a);
  }

  //==  N = 2
  template<decorator D, value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto reverse_horner_impl(D const &
                                            , T0 const &x, T1 const &a, T2 const &b) noexcept
  requires compatible_values<T0, T1> &&compatible_values<T1, T2>
  {
    using r_t = common_compatible_t<T0, T1, T2>;
    return D()(fma)(r_t(x), b, a);
  }

  //==  N >= 3
  template<decorator D,
           value T0,
           value T1,
           value T2,
           value ...Ts>
  EVE_FORCEINLINE constexpr
  auto reverse_horner_impl(D const & d
                          , T0 xx, T1 a, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, T2, Ts...>;
    auto x =  r_t(xx);
    std::array<r_t, sizeof...(args)+2> t{};
    int i = t.size()-1;
    t[i] = a;
    t[--i] = b;
    [[maybe_unused]]auto cpr = [&t, &i](auto c){t[--i] = r_t(c); return c; };
    ((cpr(args)), ...);
    return d(horner)(x, t);

  }

  //================================================================================================
  //== N+ 1  parameters (((..(x+b)*x+c)*x + ..)..) with unitary leader coefficients
  //================================================================================================
  //==  N = 0,nope one is there
  //==  N = 1
  template<decorator D, value T0>
  EVE_FORCEINLINE constexpr auto reverse_horner_impl(D const &
                                            , T0 const & x, callable_one_ const &) noexcept
  {
    return one(as(x));
  }
  //==  N = 2
  template<decorator D, value T0, value T2>
  EVE_FORCEINLINE constexpr auto reverse_horner_impl(D const &
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
  auto reverse_horner_impl(D const & d
                          , T0 xx, callable_one_ const&, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T2, Ts...>;
    std::array<r_t, sizeof...(args)+1> a;
    int i = a.size()-1;
    a[i] = b;
    auto cpr = [&a, &i](auto c){a[--i] = r_t(c); };
    ((cpr(args), ...));
    return d(horner)(xx, one, a);
  }

  //================================================================================================
  //== Reverse_Horner with iterators
  //================================================================================================
  template<decorator D, value T0, std::input_iterator IT>
  EVE_FORCEINLINE constexpr auto reverse_horner_impl( D const & d
                                            , T0 xx
                                            , IT const & first_
                                            , IT const & last_
                                            ) noexcept
  requires (compatible_values<T0, typename std::iterator_traits<IT>::value_type>)
  {
    auto first = std::make_reverse_iterator(last_);
    auto last  = std::make_reverse_iterator(first_);
    return d(horner)(xx, first, last);
  }

 //================================================================================================
  //== Reverse_Horner with iterators and unitary leader coefficient
  //================================================================================================
  template<decorator D, value T0, std::input_iterator IT>
  EVE_FORCEINLINE constexpr auto reverse_horner_impl( D const & d
                                            , T0 xx
                                           ,  callable_one_ const &
                                            , IT const & first_
                                            , IT const & last_
                                            ) noexcept
  requires (compatible_values<T0, typename std::iterator_traits<IT>::value_type>)
  {
    auto first = std::make_reverse_iterator(last_);
    auto last  = std::make_reverse_iterator(first_);
    return d(horner)(xx, one, first, last);
  }

  //================================================================================================
  //== Reverse_Horner with ranges
  //================================================================================================
  template<decorator D, value T0, range R>
  EVE_FORCEINLINE constexpr auto reverse_horner_impl(D const & d
                                        , T0 xx, R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    return reverse_horner_impl(d, xx, std::begin(r), std::end(r));
  }

  //================================================================================================
  //== Reverse_Horner with ranges and leading unitary coefficient
  //================================================================================================
  template<decorator D, value T0, range R>
  EVE_FORCEINLINE constexpr auto reverse_horner_impl(D const & d
                                            , T0 xx
                                            , callable_one_ const &
                                            , R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    return reverse_horner_impl(d, xx, one, std::begin(r), std::end(r));
  }
}
