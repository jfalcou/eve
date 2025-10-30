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
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1))
      EVE_FORCEINLINE eve::upgrade_if_t<Options, common_value_t<Ts...>>
    constexpr operator()(Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(ts...); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
      EVE_FORCEINLINE constexpr
    upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2>)
      EVE_FORCEINLINE constexpr
    eve::upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(t1, t2); }

    template<floating_value H, kumi::non_empty_product_type Tup2>
      EVE_FORCEINLINE constexpr
    eve::upgrade_if_t<Options, common_value_t<H, kumi::apply_traits_t<eve::common_value,  Tup2>>>
    operator()(H const& h, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(h, t2); }


    template<typename F, kumi::non_empty_product_type Tup2>
    requires(!value<F> && !kumi::non_empty_product_type<F>)
      EVE_FORCEINLINE constexpr
    eve::upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,  Tup2>>
    operator()(F const& f, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(f, t2); }


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
//!      constexpr auto trapz(kumi::non_empty_product_type auto const& x,
//!                           kumi::non_empty_product_type auto const& y)                   noexcept; // 1
//!      constexpr auto trapz(floating_value auto ... ys)                                   noexcept; // 2
//!      constexpr auto trapz(kumi::non_empty_product_type auto const& y)                   noexcept; // 2
//!      constexpr auto trapz(floating_value h,
//!                           kumi::non_empty_product_type auto const& y)                   noexcept; // 2
//!      constexpr auto trapz(eve::invocable f, floating_value auto ... xs)                 noexcept; // 4
//!      constexpr auto trapz(eve::invocable f, kumi::non_empty_product_type auto const& x) noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto trapz[widen](/*any of the above overloads*/)                        noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` : [real](@ref eve::floating values) ordered arguments in increasing order.
//!     * `x`,     : [tuple of real](@ref eve::floating values) ordered arguments in increasing order.
//!     * `y`      : tuple of real arguments
//!     * `h`      : floating value scaling the abscissas
//!     * `f`      : invocable
//!
//!    **Return value**
//!
//!      * 1. Computes elementwise the integral of the piecewise linear function defined by \$f(x_i) = y_i\f$ (trapezoidal rule)
//!      * 2. the missing `x` parameter is assumed equal to be an arithmetic progression of common difference h (1 if h is omitted).
//!      * 3. the missing `y` parameter is assumed equal to the call of f applied to the x elements
//!      * 3. the tuple `x` must have its elements sorted in increasing order.
//!
//!  @note definition of `f` or of `y` ?
//!      - If `f` is a paramater the `y` values are defined by  \$y_i = \mathrm{f}(x_i)\f$ and `x` or `xs`must be defined
//!      - If `y` (or `ys...`) is a parameter `f` is defined by  \$f(x_i) = y_i\f$. and the values of \f$x_i\f$ are not needed
//!        as thet are equally spaced with space `h` (defaulted to one).
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
      auto upgrade = [](auto a){ return eve::convert(a, eve::as<eve::element_type_t<eve::upgrade_t<decltype(a)>>>()); };
      if constexpr(floating_value<HPT1>)
      {

        if constexpr(O::contains(widen))
          return trapz[o.drop(widen)](upgrade(x), kumi::map(upgrade, y));
        else
          return x*trapz[o](y);
      }
      else if constexpr(kumi::is_product_type<HPT1>::value)
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
      else
      {
        return trapz[o](y, kumi::map(x, y));
      }
    }
  }
}
