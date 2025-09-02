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
  struct dot_t : tuple_callable<dot_t, Options, kahan_option, widen_option>
  {
    template<eve::value... Ts>
    requires(sizeof...(Ts) > 0 && eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr common_value_t<Ts...> operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<eve::value... Ts>
    requires(sizeof...(Ts) > 0 && eve::same_lanes_or_scalar<Ts...> && Options::contains(widen))
      EVE_FORCEINLINE common_value_t<upgrade_t<Ts>... >
    constexpr operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2>)
      EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(kumi::cat(t1, t2)); }

    EVE_CALLABLE_OBJECT(dot_t, dot_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dot
//!   @brief `elementwise_callable` object computing elementwise the dot product
//!     of the vector of the first half parameter by thevector of the last half.
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
//!      constexpr auto dot(kumi::tuple xs, kumi::tuple ys)            noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto dot[kahan](/*any of the above overloads*/)     noexcept; // 3
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
//!    1. dot product. \f$\sum_s x_s*y_s\f$.
//!    2. use teh content of the tuples
//!    3. With kahan option the result is more accurately computed using a compensated kahan like algorithm.
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

    template<typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    dot_(EVE_REQUIRES(cpu_), O const & o, Ts... args) noexcept
    requires(sizeof...(Ts) > 1  && sizeof...(Ts)%2 == 0)
    {
      if constexpr(sizeof...(Ts) == 2)
        return eve::mul(args...);
      else
      {
        using r_t =  eve::common_value_t<Ts...>;
        if constexpr(O::contains(widen))
          return dot[o.drop(widen)](upgrade(r_t(args))...);
        else
        {
          auto coeffs = eve::zip(r_t(args)...);
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
  }
}
