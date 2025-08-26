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
  struct dot_t : callable<dot_t, Options, kahan_option>
  {
    template<eve::value T,  eve::value U>
    requires(eve::same_lanes_or_scalar<T, U>)
      constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    template<eve::value... Ts>
    requires(sizeof...(Ts) >= 2 && eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr common_value_t<Ts...> operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

//     template<eve::value... Ts>
//     requires(sizeof...(Ts) >= 2 && eve::same_lanes_or_scalar<Ts...> && Options::contains(widen))
//       EVE_FORCEINLINE common_value_t<upgrade_t<Ts>... >
//     constexpr operator()(Ts...ts) const noexcept
//     {
//       return EVE_DISPATCH_CALL(ts...);
//     }


    template<eve::detail::range R1, eve::detail::range R2>
    EVE_FORCEINLINE constexpr
    eve::common_value_t<typename R1::value_type, typename R2::value_type>
    operator()(R1 const& t1,  R2 const & t2) const noexcept
    {
      EVE_ASSERT( std::distance(begin(t1), end(t1)) == std::distance(begin(t2), end(t2)),
                  "[eve::dot]:ranges sizes are not equal");
      return EVE_DISPATCH_CALL(t1, t2);
    }
//     template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup>)
//     EVE_FORCEINLINE constexpr
//     kumi::apply_traits_t<eve::common_value,Tup>
//     operator()(Tup const& t) const noexcept { return EVE_DISPATCH_CALL(t); }

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
//!      constexpr auto dot(Range r1. xs, auto value... ys, Range r2)  noexcept; // 2
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
//!    2. use teh content of the ranges.
//!    3. With kahan option the result is more accurately computed using a compensated algorithm.
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
    template<value T, value U, callable_options O>
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

    template<eve::detail::range R1, eve::detail::range R2, callable_options O>
    EVE_FORCEINLINE constexpr auto
    dot_(EVE_REQUIRES(cpu_), O const & o, R1 r1, R2 r2) noexcept
    {
      using r_t   = common_value_t<typename R1::value_type, typename R2::value_type>;
      auto fr1 = begin(r1);
      auto lr1  = end(r1);
      if( fr1 == lr1 ) return r_t(0);
      using std::advance;
      auto fr2 = begin(r2);
      auto cr2 = fr2;
      auto cr1 = fr1;

      advance(cr1, 1);
      advance(cr2, 1);
      if constexpr(O::contains(kahan))
      {
        auto [sum,err] = eve::two_prod(*fr1, *fr2);
        auto step = [&](auto a, auto b) {
          auto[s1, e1] = eve::two_fma_approx(a, b, sum);
          err += e1;
          sum = s1;
        };
        for(; cr1 != lr1; advance(cr1, 1), advance(cr2, 1) ) step(*cr1, *cr2);
        return sum+err;
      }
      else
      {
        auto sum = mul[o](*fr1, *fr2);
        for(; cr1 != lr1; advance(cr1, 1), advance(cr2, 1) ) sum+= mul[o](*cr1, *cr2);
        return sum;
      }
    }
  }

}
