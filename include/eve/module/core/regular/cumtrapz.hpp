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
#include <eve/module/core/regular/average.hpp>
#include <eve/module/core/regular/cumsum.hpp>
#include <eve/module/core/regular/diff.hpp>
#include <eve/module/core/detail/tuple_array_utils.hpp>

namespace eve
{
  template<typename Options>
  struct cumtrapz_t : callable<cumtrapz_t, Options, widen_option>
  {
    template<typename T>
    using return_type = eve::upgrade_if_t<Options,T>;

    template<value... Ts>
    using result = kumi::result::fill_t<sizeof...(Ts), return_type<eve::common_value_t<Ts...>>>;

    template<product_type T>
    using tuple_result = kumi::result::fill_t< T::size() , return_type<kumi::apply_traits_t<eve::common_value, T>>>;

    template<value T, value ...Ts>
    EVE_FORCEINLINE constexpr result<T, Ts...>
    operator()(T t, Ts ... ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t, ts...);
    }

    template<non_empty_product_type T>
    EVE_FORCEINLINE constexpr tuple_result<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    template<floating_value X, non_empty_product_type Y>
    EVE_FORCEINLINE constexpr tuple_result<Y>
    operator()(X dx, Y y) const noexcept
    {
      return EVE_DISPATCH_CALL(dx, y);
    }

    template<non_empty_product_type X, non_empty_product_type Y>
    EVE_FORCEINLINE constexpr tuple_result<Y>
    operator()(X x, Y y) const noexcept
    {
      return EVE_DISPATCH_CALL(x, y);
    }

    template<typename F, non_empty_product_type X>
    requires (std::invocable<F, tuple_result<X>>)
    EVE_FORCEINLINE constexpr tuple_result<X>
    operator()(F f, X x) const noexcept
    {
      return EVE_DISPATCH_CALL(f, x);
    }

    template<std::invocable F, value ...Ts>
    EVE_FORCEINLINE constexpr result<Ts...>
    operator()(F f, Ts ... ts) const noexcept
    {
      return EVE_DISPATCH_CALL(f, kumi::make_tuple(ts...));
    }

    EVE_CALLABLE_OBJECT(cumtrapz_t, cumtrapz_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var cumtrapz
///!   @brief `callable` converting a pack of values into a tuple of the cumulative
///!   trapezoidal of its values.
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
//!      constexpr auto trapz(eve::non_empty_product_type auto const& x,
//!                           eve::non_empty_product_type auto const& y)                   noexcept; // 1
//!      constexpr auto trapz(floating_value auto ... ys)                                  noexcept; // 2
//!      constexpr auto trapz(eve::non_empty_product_type auto const& y)                   noexcept; // 2
//!      constexpr auto trapz(floating_value h,
//!                           eve::non_empty_product_type auto const& y)                   noexcept; // 2
//!      constexpr auto trapz(eve::invocable f, floating_value auto ... xs)                noexcept; // 4
//!      constexpr auto trapz(eve::invocable f, eve::non_empty_product_type auto const& x) noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto trapz[widen](/*any of the above overloads*/)                       noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` : [real](@ref eve::floating values) ordered arguments in increasing order.
//!     * `x`,     : [tuple of real](@ref eve::floating values) ordered arguments in increasing order.
//!     * `y`      : tuple of real arguments
//!     * `h`      : floating value scaling the abscissas
//!     * `f`      : invocable requiring f :common_value_t<Xs...>() -> common_value_t<Xs...>.
//!                  If widen is used, `f` must be usable with the upgraded type.
//!
//!    **Return value**
//!
//!     1. return a kumi tuple of the values of the cumulated trapz of all `xs` converted to
//!         the element type of the common value of the `xs`. the xs have to be sorted in ascending order.
//!     2. same as 1., using the tuple elements.
//!     3. same of 1. or 2., but upgrading the elements of the result.
//!
//!  @note Where [trapz}(@ref eve::trapz) returns only the overall integral, `cumtrapz` returns a tuple
//!        of the current partialintegral values.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia trapezoidal rule](https://en.wikipedia.org/wiki/Trapezoidal_rule)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/cumtrapz.cpp}
//================================================================================================
  inline constexpr auto cumtrapz = functor<cumtrapz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {

    template <eve::product_type PT, callable_options O>
    EVE_FORCEINLINE constexpr auto cumtrapz_(EVE_REQUIRES(cpu_), O const & o, PT tup) noexcept
    {
      if constexpr(PT::size() == 0)
        return kumi::make_tuple();
      else
      {
        if constexpr(PT::size() == 0)
          return kumi::make_tuple();
        else if constexpr(O::contains(widen))
          return cumsum[o.drop(widen)](upg(tup));
        else
        {
          using r_t = kumi::apply_traits_t<eve::common_value, PT>;
          auto w = kumi::windows<2>(tup);
          auto r = kumi::map(eve::average, w);
          return push_front(eve::cumsum(r), r_t(0));
        }
      }
    }

    template <floating_value DX, eve::product_type PT, callable_options O>
    EVE_FORCEINLINE constexpr auto cumtrapz_(EVE_REQUIRES(cpu_), O const & o, DX dx, PT tup) noexcept
    {
      if constexpr(PT::size() == 0)
        return kumi::make_tuple();
      else
      {
        auto dxtup =  kumi::map([dx](auto m){return dx*m; }, tup);
        return cumtrapz[o](dxtup);
       }
    }

    template <eve::product_type PTX, eve::product_type PTY, callable_options O>
    EVE_FORCEINLINE constexpr auto cumtrapz_(EVE_REQUIRES(cpu_), O const & o, PTX x, PTY tup) noexcept
    requires( PTX::size() == PTY::size())
    {
      if constexpr(PTX::size() == 0)
        return kumi::make_tuple();
      else if constexpr(O::contains(widen))
        return cumsum[o.drop(widen)](upg(x), upg(tup));
      else
      {
        using r1_t = kumi::apply_traits_t<eve::common_value, PTX>;
        using r2_t = kumi::apply_traits_t<eve::common_value, PTY>;
        using r_t = eve::common_value_t<r1_t, r2_t>;
        auto w = kumi::windows<2>(tup);
        auto dx = eve::diff(x);
        auto avg = kumi::map(eve::average, w);
        auto rdx =  kumi::map([](auto a, auto b) { return -a*b; }, avg, dx);
        return push_front(eve::cumsum(rdx), r_t(0));
      }
    }

    template< typename F, eve::product_type PTX, callable_options O>
    EVE_FORCEINLINE constexpr auto cumtrapz_(EVE_REQUIRES(cpu_), O const & o, F f, PTX x) noexcept
    {
      if constexpr(PTX::size() == 0)
        return kumi::make_tuple();
      else if constexpr(O::contains(widen))
        return cumsum[o.drop(widen)](f, upg(x));
      else
      {
        auto fx = kumi::map(f, x);;
        return cumtrapz(x, fx);
      }
    }

    template<value T, value ...Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    cumtrapz_(EVE_REQUIRES(cpu_), O const & o, T t0, Ts... ts) noexcept
    {
      return eve::cumtrapz[o](kumi::make_tuple(t0, ts...));
    }

  }
}
