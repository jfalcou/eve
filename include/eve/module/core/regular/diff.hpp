//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/traits/updown.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/dot.hpp>
#include <eve/module/core/regular/average.hpp>

namespace eve
{

  template<typename Options>
  struct diff_t : callable<diff_t, Options, widen_option>
  {

    template<eve::floating_value T0, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1))
      EVE_FORCEINLINE auto constexpr operator()(T0 t0, Ts...ts) const -> decltype(kumi::tuple{ts...})// const noexcept
    { return EVE_DISPATCH_CALL(t0, ts...); }

    template<eve::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
      EVE_FORCEINLINE constexpr
    auto  operator()(Tup const& t) const  -> decltype(kumi::pop_front(t)) const// noexcept
    { return EVE_DISPATCH_CALL(t); }

    template<size_t N, eve::floating_value T0, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1))
      EVE_FORCEINLINE auto constexpr operator()(kumi::index_t<N> n, T0 t0, Ts...ts) const
      -> decltype(kumi::split(kumi::tuple(t0, ts...), sizeof...(ts)-N+1))//  noexcept
    { return EVE_DISPATCH_CALL(n, t0, ts...); }

    template<size_t N, eve::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
      EVE_FORCEINLINE constexpr
    auto  operator()(kumi::index_t<N>, Tup t) const
      -> std::decay_t<decltype(get<0>(kumi::split(t, kumi::index_t<kumi::size_v<Tup>-N>{})))> const// noexcept
    { return EVE_DISPATCH_CALL(kumi::index_t<N>{}, t); }

    EVE_CALLABLE_OBJECT(diff_t, diff_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var diff
//!   @brief `tuple_callable` computing the nth  adjacent differences of its arguments.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto diff(eve::floating_value auto const& xs...)                                        noexcept; // 1
//!      constexpr auto diff(eve::non_empty_product_type auto const& x)                                    noexcept; // 1
//!      typename<auto N> constexpr auto diff(kumi::index_t<N>, eve::floating_value auto const& xs...)     noexcept; // 2
//!      typename<auto N> constexpr auto diff(kumi::index_t<N>,eve::non_empty_product_type auto const& x)  noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` : [real](@ref eve::floating values) arguments
//!     * `x`      : kumi::tuple of arguments
//!
//!    **Return value**
//!
//!      * 1. Return a tuple containing the elementwise adjacent differences of the parameters or of the elements of the tuple.
//!      * 2. Return a tuple containing the elementwise Nth adjacent differences of the parameters or of the elements of the tuple.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia divided differences](https://en.cppreference.com/w/cpp/types/integral_constant.html)
//!  @groupheader{Example}
//!  @godbolt{doc/core/diff.cpp}
//================================================================================================
  inline constexpr auto diff = functor<diff_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<eve::non_empty_product_type PT , callable_options O>
     EVE_FORCEINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const & o, PT x) noexcept
    {
      if constexpr(O::contains(widen))
        return diff[o.drop(widen)](kumi::map(upgrade, x));
      else
        return kumi::map(eve::sub[o], kumi::pop_front(x), kumi::pop_back(x));
    }

    template<floating_value... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const & o, Ts... args) noexcept
    {
      using r_t =  eve::common_value_t<Ts...>;
      if constexpr(O::contains(widen))
        return diff[o.drop(widen)](upgrade(r_t(args))...);
      else
        return eve::diff[o](kumi::make_tuple(args...));
    }

    template<size_t N, eve::non_empty_product_type PT , callable_options O>
    EVE_FORCEINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const & o, kumi::index_t<N> n, PT & x) noexcept
    {
      if constexpr(O::contains(widen))
        return diff[o.drop(widen)](n, kumi::map(upgrade, x));
      else
        if constexpr(N >= kumi::size_v<PT>) return kumi::tuple{};
        else if constexpr(N == 0)           return x;
        else if constexpr(N == 1)           return diff(x);
        else                                return diff(kumi::index_t<N-1>{}, diff(x));
    }

    template<size_t N, floating_value... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const & o, kumi::index_t<N> n, Ts... args) noexcept
    {
      using r_t =  eve::common_value_t<Ts...>;
      if constexpr(O::contains(widen))
        return diff[o.drop(widen)](upgrade(r_t(args))...);
      else
        return eve::diff[o](n, kumi::make_tuple(args...));
    }
  }

}
