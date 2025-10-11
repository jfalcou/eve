//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/dot.hpp>
#include <eve/module/core/decorator/core.hpp>
namespace eve
{
  template<typename Options>
  struct covariance_t : tuple_callable<covariance_t, Options, kahan_option, widen_option, unbiased_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && !Options::contains(widen))
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && Options::contains(widen))
    EVE_FORCEINLINE common_value_t<upgrade_t<T0>, upgrade_t<T1>, upgrade_t<Ts>... >
    constexpr operator()(T0 t0, T1 t1, Ts...ts)  const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
    { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
    { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    eve::upgrade_t<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(kumi::cat(t1, t2)); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(kumi::cat(t1, t2)); }

    EVE_CALLABLE_OBJECT(covariance_t, covariance_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var covariance
//!   @brief `elementwise_callable` object computing the elementwise  covariance product
//!     of the vector of the first half parameters by the vector of the last half.
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
//!      constexpr auto covariance(auto value... xs, auto value... ys)        noexcept; // 1
//!      constexpr auto covariance(kumi::tuple xs, kumi::tuple ys)            noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto covariance[unbiased](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto covariance[widen]   (/*any of the above overloads*/)  noexcept; // 4
//!      constexpr auto covariance[kahan]   (/*any of the above overloads*/)  noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs`, `ys`  :  [floating value arguments](@ref eve::value) or tuples of floating value arguments.
//!
//!    **Return value**
//!
//!    1. covariance product. \f$\frac1N\sum_s (x_s-\bar{x_s})*(y_s-\bar{y_s})\f$.
//!       where N is the number of `x_s` (minus 1 if `unbiased` option is used).
//!    2. use the content of the tuples
//!    3. see 1.
//!    4. Uses a compensated kahan-like algorithm to compute the result more accurately
//!    5. Uses the upgraded type for computations and result
//!
//!  @see [`welford_covariance`](@ref welford_variance) for incremental or parallel covariance and averages computations.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/covariance.cpp}
//================================================================================================
  inline constexpr auto covariance = functor<covariance_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto covariance_(EVE_REQUIRES(cpu_), O const & o, Ts... args) noexcept
    requires(sizeof...(Ts) > 1  && sizeof...(Ts)%2 == 0)
    {
      using r_t =  eve::common_value_t<Ts...>;
      constexpr auto siz = sizeof...(Ts)/2;
      if constexpr(siz == 1) return eve::zero(eve::as<r_t>());
      else
      {
        if constexpr(O::contains(widen)) return covariance[o.drop(widen)](upgrade(r_t(args))...);
        else
        {
          auto coeffs = eve::zip(r_t(args)...);
          auto[f,s]   = kumi::split(coeffs, kumi::index<siz>);
          auto avgf = eve::average[o](f);
          auto avgs = eve::average[o](s);
          r_t cov{};
          if constexpr(O::contains(raw))
            cov = kumi::sum( kumi::map([avgf, avgs](auto a, auto b) { return (a-avgf)*(b-avgs); }, f, s));
          else
          {
            auto fc =  kumi::map([avgf](auto a) { return (a-avgf); }, f);
            auto sc =  kumi::map([avgs](auto a) { return (a-avgs); }, s);
            cov = eve::dot[o](fc, sc);
          }
          if constexpr(O::contains(unbiased))
            return cov/dec(siz);
          else
            return cov/siz;
        }
      }
    }
  }
}
