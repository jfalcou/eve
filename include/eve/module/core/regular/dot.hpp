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

namespace eve
{
  template<typename Options>
  struct dot_t : tuple_callable<dot_t, Options, kahan_option>
  {
    template<eve::value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

     template<value T0, eve::value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && !Options::contains(widen))
    EVE_FORCEINLINE constexpr common_value_t<T0,T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<value T0, eve::value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && Options::contains(widen))
    EVE_FORCEINLINE common_value_t<upgrade_t<T0>, upgrade_t<T1>, upgrade_t<Ts>... >
    constexpr operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(dot_t, dot_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dot
//!   @brief `elementwise_callable` object computing elementwise the dot product of the two parameters.
//!
//!   @warning This is not a reduction ! For reals the dot product is the product
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
//!      constexpr auto dot(auto value... xs, auto value... ys)        noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto dot[kahan](/*any of the above overloads*/)     noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`  :  [value arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    dot product. \f$\sum_s x_s*y_s\f$.
//!    With kahan option the result is more accurately computed using a compensated algorithm.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/dot.cpp}
//================================================================================================
  inline constexpr auto dot = functor<dot_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    dot_(EVE_REQUIRES(cpu_), O const &, T a,  U b) noexcept
    {
      return mul(a, b);
    }

    template<typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    dot_(EVE_REQUIRES(cpu_), O const &  , Ts... args) noexcept
    requires(sizeof...(Ts) > 2  && sizeof...(Ts)%2 == 0)
    {
      using r_t =  eve::common_value_t<Ts...>;
      auto coeffs = kumi::tuple{r_t(args)...};
      auto[f,s]   = kumi::split(coeffs, kumi::index<sizeof...(Ts)/2>);
      if constexpr(O::contains(kahan))
      {
        auto[f0,fs] = kumi::split(f, kumi::index<1>);
        auto[s0,ss] = kumi::split(s, kumi::index<1>);

        auto [sum,error] = eve::two_prod(get<0>(f0), get<0>(s0));

        kumi::for_each( [&](auto a, auto b) {
                          auto[s1, e1] = eve::two_fma_approx(a, b, sum);
                          error += e1;
                          sum    = s1;
                        }, fs, ss
                      );

        return sum + error;
      }
      else
      {
        return kumi::sum( kumi::map([](auto a, auto b) { return a*b; }, f, s));
      }
    }
  }
}
