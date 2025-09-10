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
#include <eve/module/core/regular/sum_of_prod.hpp>
#include <eve/module/core/regular/two_fma_approx.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve
{

  template<typename Options>
  struct average_t : tuple_callable<average_t, Options, upper_option, lower_option, strict_option,
                                                        widen_option, kahan_option>
  {

    template<typename... Ts>
    requires( (sizeof...(Ts) !=  0) && eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen) )
    EVE_FORCEINLINE common_value_t<Ts...>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires( (sizeof...(Ts) !=  0) && eve::same_lanes_or_scalar<Ts...> && Options::contains(widen) )
    EVE_FORCEINLINE upgrade_t<common_value_t<Ts...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    EVE_CALLABLE_OBJECT(average_t, average_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var average
//!   @brief `tuple_callable` computing the arithmetic mean of its arguments.
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
//!      constexpr auto average(eve::integral_value auto x, eve::integral_value auto y)             noexcept; // 1
//!      constexpr auto average(eve::floating_value auto x, eve::floating_value auto ... xs)        noexcept; // 2
//!      constexpr auto average(kumi::non_empty_product_type auto const& tup)                       noexcept; // 3
//!
//!      // Lanes masking
//!      constexpr auto average[conditional_expr auto c](/* any of the above overloads */)          noexcept; // 4
//!      constexpr auto average[logical_value auto m](/* any of the above overloads */)             noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto average[raw] (/* any of the above overloads */)                             noexcept; // 5
//!      constexpr auto average[upper](eve::value auto x, eve::value auto y)                        noexcept; // 6
//!      constexpr auto average[lower](eve::value auto x, eve::value auto y)                        noexcept; // 7
//!      constexpr auto average[upper][strict](eve::value auto x, eve::value auto y)                noexcept; // 6
//!      constexpr auto average[lower][strict](eve::value auto x, eve::value auto y)                noexcept; // 7
//!      constexpr auto average[widen](/* any of the above overloads */)                            noexcept; // 8
//!      constexpr auto average[kahan](/* any of the above overloads */)                            noexcept; // 9
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [integral value](@ref eve::integral_value) arguments.
//!     * `xs...`: [floating value](@ref eve::floating_value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `n': number of elements on which the mean was previously computed
//!     * `prvavg': previously computed average of n elements.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    The value of the arithmetic mean  of the arguments is returned.
//!
//!     1. For two integral parameters half the sum of `x` and `y`. No overflow occurs.
//!        If the sum is odd, the result is a rounded value at a distance guaranteed
//!        to be less than or equal to 0.5 of the average floating value, but may differ
//!        by unity from the truncation given by `(x+y)/2`. Moreover, as some architectures provide
//!        simd intrinsics to perform the operation, the scalar results may differ by one unit from
//!        simd ones which are system dependent.
//!
//!        However the `dowward` (respectively `upward`) options can be used to ensure the result is equivalent to
//!        the integral conversion of `floor((x+y)/2)`, (respectively  `ceil((x+y)/2)`).
//!     2. the arithmetic mean of its arguments. No overflow occurs.
//!     3. the arithmetic mean of the tuple arguments. No overflow occurs.
//!     4. [The operation is performed conditionnaly](@ref conditional)
//!     5. No provision is made to avoid overflows for more than 2 parameters.
//!     6. The average is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!        to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!        ensures generally faster computation, but strict inequality.
//!        For integral type entries, these are similar to `ceil((x+y)/2)`, but converted to an integral value.
//!     7. The average is computed in a 'round toward \f$ +\infty\f$ mode. The result is guaranted
//!        to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!        ensures generally faster computation, but strict inequality.
//!        For integral type entries,  these are similar to `floor((x+y)/2)` but converted to an integral value.
//!     8. The average is computed in the double sized element type (if available).
//!     9. Kahan like Compensated algorithm for better precision.
//!
//!  @note
//!     1.  with raw option is a spurious overflow can be obtained.
//!     2.  `mean`can be used as an alias to `average`.
//!
//!
//!  @groupheader{External references}
//!   *  [Wikipedia Mean](https://en.wikipedia.org/wiki/Mean)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/average.cpp}
//================================================================================================
  inline constexpr auto average = functor<average_t>;
//================================================================================================
//! @}
//================================================================================================

}

namespace eve::detail
{

  template<value T0, value ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  average_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  requires(!O::contains(welford))
  {
    using r_t =  eve::common_value_t<T0, Ts...>;
    using e_t =  eve::element_type_t<r_t>;
    using C = rbr::result::fetch_t<condition_key, O>;
    if constexpr( !std::same_as<C,ignore_none_> )
    {
      auto cond = o[condition_key];
      auto z = average[o.drop(condition_key)](a0, args...);
      return if_else(cond, z, r_t(a0));
    }
    else if constexpr(O::contains(widen))
    {
      return average[o.drop(widen)](upgrade(a0), upgrade(args)...);
    }
    else if constexpr(sizeof...(Ts) == 0)
      return a0;
    else if constexpr(sizeof...(Ts) == 1)
    {
      const auto b = r_t(args...);
      const auto a = r_t(a0);
      if constexpr(integral_value<r_t>)
      {
       if constexpr(O::contains(upper))
          return (a | b) - ((a ^ b) >> 1);   //compute ceil( (a+b)/2 )
        else
          return (a & b) + ((a ^ b) >> 1);   //compute floor( a+b)/2 )  default
      }
      else
      {
        const auto h = eve::half(eve::as<e_t>());
        return fma[o][pedantic](a, h, b*h);
      }
    }
    else
    {
      constexpr auto N = sizeof...(Ts)+1;
      constexpr e_t invn = 1/(e_t(N));
      if constexpr(O::contains(raw))
      {
        if constexpr(integral_value<r_t>)
        {
          return add[o.drop(raw)](a0, args...)/N;
        }
        else
        {
          return eve::mul[o](add[o.drop(raw)](a0, args...), invn);
        }
      }
      else if constexpr(O::contains(kahan))
      {
        auto pair_add = [invn](auto pair0, auto r1){
          auto [r, e0] = pair0;
          auto [s, e1] = eve::two_fma_approx(r1, invn, r);
          return zip(s, e0+e1);
        };
        auto p0 = two_prod(r_t(a0), invn);
        ((p0 = pair_add(p0,args)),...);
        auto [r, e] = p0;
        return r+e;
      }
      else
      {
        r_t that(a0 * invn);
        auto lfma = fma[o];
        auto  next = [invn, lfma](auto avg, auto x) { return lfma(x, invn, avg); };
        ((that = next(that, r_t(args))), ...);
        return that;
      }
    }
  }



//   template<kumi::non_empty_product_type Tup, callable_options O>
//   EVE_FORCEINLINE constexpr auto average_(EVE_REQUIRES(cpu_), O const & o, Tup tup) noexcept
//   requires(!O::contains(welford))
//   {
//     return kumi::apply([o](auto...m){return average[o](m...);}, tup);
//   }

//   template<kumi::non_empty_product_type Tup, callable_options O>
//   EVE_FORCEINLINE constexpr auto average_(EVE_REQUIRES(cpu_), O const & o, std::size_t n, Tup tup) noexcept
//   requires(O::contains(welford))
//   {
//     return kumi::apply([n, o](auto...m){return average[o](n, m...);}, tup);
//   }

}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/average.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/average.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/average.hpp>
#endif
