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

#include <iostream>
namespace eve
{

  template<typename Options>
  struct trapz_t : callable<trapz_t, Options, widen_option, kahan_option>
  {

    template<floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1) && !Options::contains(widen))
      EVE_FORCEINLINE common_value_t<Ts...>
    constexpr operator()(Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(ts...); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(t1, t2); }

    template<floating_value H, kumi::non_empty_product_type Tup2>
    requires(!Options::contains(widen))
    EVE_FORCEINLINE constexpr
    common_value_t<H, kumi::apply_traits_t<eve::common_value,  Tup2>>
    operator()(H const& h, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(h, t2); }

    /////////////////////////////////////

    template<floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1) && Options::contains(widen))
      EVE_FORCEINLINE upgrade_t<common_value_t<Ts...>>
    constexpr operator()(Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(ts...); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    upgrade_t<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(t1, t2); }

    template<floating_value H, kumi::non_empty_product_type Tup2>
    requires(Options::contains(widen))
    EVE_FORCEINLINE constexpr
    upgrade_t<common_value_t<H, kumi::apply_traits_t<eve::common_value,  Tup2>>>
    operator()(H const& h, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(h, t2); }


//              template<floating_value... Ts>
//     requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1))
//       EVE_FORCEINLINE eve::upgrade_if_t<Options, common_value_t<Ts...>>
//     constexpr operator()(Ts...ts) const noexcept
//     { return EVE_DISPATCH_CALL(ts...); }

//     template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup>)
//       EVE_FORCEINLINE constexpr
//     upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>
//     operator()(Tup const& t) const noexcept
//     { return EVE_DISPATCH_CALL(t); }

//     template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
//     requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2>)
//       EVE_FORCEINLINE constexpr
//     eve::upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
//     operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(t1, t2); }

//     template<floating_value H, kumi::non_empty_product_type Tup2>
//       EVE_FORCEINLINE constexpr
//     eve::upgrade_if_t<Options, common_value_t<H, kumi::apply_traits_t<eve::common_value,  Tup2>>>
//     operator()(H const& h, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(h, t2); }

    EVE_CALLABLE_OBJECT(trapz_t, trapz_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var trapz
//!   @brief `tuple_callable` object applying the trapezoidal composite rule to its arguments.
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
//!      constexpr auto trapz(floating_value auto ... ys)                               noexcept; // 1
//!      constexpr auto trapz(kumi::non_empty_product_type auto const& y)               noexcept; // 1
//!      constexpr auto trapz(floating_value h,
//!                           kumi::non_empty_product_type auto const& y)               noexcept; // 2
//!      constexpr auto trapz(kumi::non_empty_product_type auto const& x,
//                            kumi::non_empty_product_type auto const& y)               noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto trapz[widen](/*any of the above overloads*/)                    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `ys ...` : [real](@ref eve::floating values) ordered arguments in increasing order.
//!     * `x`,     : [tuple of real](@ref eve::floating values) ordered arguments in increasing order.
//!     * `y`      : tuples of real arguments
//!
//!    **Return value**
//!
//!      Computes elementwise the integral of the piecewise linear function defined by \$f(x_i) = y_i\f$ (trapezoidal rule)
//!
//!      * 1. the missing `x` parameter is assumed equal to be an arithmetic progression of common difference 1.
//!      * 2. the missing `x` parameter is assumed equal to be an arithmetic progression of common difference `h`.
//!      * 3. the tuple `x` must have its elements sorted in increasing order.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia taxicab norm](https://en.wikipedia.org/wiki/Norm_(mathematics))
//!  @groupheader{Example}
//!  @godbolt{doc/core/trapz.cpp}
//================================================================================================
  inline constexpr auto trapz = functor<trapz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<kumi::non_empty_product_type PT , callable_options O>
     EVE_FORCEINLINE constexpr auto
    trapz_(EVE_REQUIRES(cpu_), O const & o, PT tup) noexcept
    {
      if constexpr(O::contains(widen))
        return trapz[o.drop(widen)](kumi::map(upgrade, tup));
      else
        return eve::add[o](tup)-eve::average[o](kumi::front(tup), kumi::back(tup));
    }

    template<floating_value... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    trapz_(EVE_REQUIRES(cpu_), O const & o, Ts... args) noexcept
    {
      using r_t =  eve::common_value_t<Ts...>;
      if constexpr(O::contains(widen))
        return trapz[o.drop(widen)](upgrade(r_t(args))...);
      else
        return eve::trapz[o](kumi::make_tuple(args...));
    }

    template<typename HPT1 ,kumi::non_empty_product_type PT2, callable_options O>
    EVE_FORCEINLINE constexpr auto
    trapz_(EVE_REQUIRES(cpu_), O const & o, HPT1 x, PT2 y) noexcept
    {
      if constexpr(floating_value<HPT1>)
      {
        if constexpr(O::contains(widen))
          return trapz[o.drop(widen)](upgrade(x), kumi::map(upgrade, y));
        else
          return x*trapz[o](y);
      }
      else
      {
       if constexpr(O::contains(widen))
         return trapz[o.drop(widen)](kumi::map(upgrade, x), kumi::map(upgrade, y));
       else
        {
          auto adjdiff =  kumi::map(eve::sub[o], kumi::pop_front(x), kumi::pop_back(x));
          auto adjsum  =  kumi::map(eve::add[o], kumi::pop_front(y), kumi::pop_back(y));
          return eve::dot[o](adjsum, adjdiff)/2;
        }
      }
    }

  }
}
