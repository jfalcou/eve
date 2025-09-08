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
#include <iostream>

namespace eve
{
  namespace detail
  {
    template < typename T> struct wf
    {
      using wf_t = T;

      wf() : avg_(T(0)), n_(1){}
      wf(auto avg,  std::size_t n) : avg_(avg), n_(n){}
      operator T()   const  noexcept {return avg_; };
      std::size_t n()const  noexcept {return n_; };

      //  private :
     T avg_;
     std::size_t n_;
   };

    template<typename>    struct is_wf_helper          : public std::false_type{};
    template<typename T>  struct is_wf_helper<wf<T>>   : public std::true_type{};
    template<typename T>  struct is_wf                 : public is_wf_helper<std::remove_cv_t<T>>::type{};
  }

  template<typename Options>
  struct mean_value_t : callable<mean_value_t, Options, raw_option, upper_option,
                                    lower_option, strict_option, kahan_option,
                                    widen_option, welford_option>
  {
     template<value... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen))
       EVE_FORCEINLINE constexpr  detail::wf<common_value_t<Ts...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename WF, value... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen) && detail::is_wf<WF>::value)
      EVE_FORCEINLINE constexpr detail::wf<common_value_t<typename WF::wf_t, Ts...>>
    operator()(WF w, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(w, ts...);
    }

    template<typename WF0, typename WF1>
    requires(detail::is_wf<WF0>::value && detail::is_wf<WF1>::value)
    EVE_FORCEINLINE constexpr detail::wf<common_value_t<typename WF0::wf_t,typename WF1::wf_t>>
    operator()(WF0 w0, WF1 w1) const noexcept
    {
      return EVE_DISPATCH_CALL(w0, w1);
    }

    EVE_CALLABLE_OBJECT(mean_value_t, mean_value_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var mean_value
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
//!      constexpr auto mean_value(eve::integral_value auto x, eve::integral_value auto y)             noexcept; // 1
//!      constexpr auto mean_value(eve::floating_value auto x, eve::floating_value auto ... xs)        noexcept; // 2
//!      constexpr auto mean_value(kumi::non_empty_product_type auto const& tup)                       noexcept; // 3
//!
//!      // Lanes masking
//!      constexpr auto mean_value[conditional_expr auto c](/* any of the above overloads */)          noexcept; // 4
//!      constexpr auto mean_value[logical_value auto m](/* any of the above overloads */)             noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto mean_value[raw] (/* any of the above overloads */)                             noexcept; // 5
//!      constexpr auto mean_value[upper](eve::value auto x, eve::value auto y)                        noexcept; // 6
//!      constexpr auto mean_value[lower](eve::value auto x, eve::value auto y)                        noexcept; // 7
//!      constexpr auto mean_value[upper][strict](eve::value auto x, eve::value auto y)                noexcept; // 6
//!      constexpr auto mean_value[lower][strict](eve::value auto x, eve::value auto y)                noexcept; // 7
//!      constexpr auto mean_value[widen](/* any of the above overloads */)                            noexcept; // 8
//!      constexpr auto mean_value[kahan](/* any of the above overloads */)                            noexcept; // 9
//!      constexpr auto mean_value[welford] (eve::floating_value auto ... x)                           noexcept; // 10
//!      constexpr auto mean_value[welford](size_t n,  eve::floating_value auto prevavg,
//!                                                 eve::floating_value auto ... x)                 noexcept; // 11
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [integral value](@ref eve::integral_value) arguments.
//!     * `xs...`: [floating value](@ref eve::floating_value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `n': number of elements on which the mean was previously computed
//!     * `prvavg': previously computed mean_value of n elements.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    The value of the arithmetic mean  of the arguments is returned.
//!
//!     1. For two integral parameters half the sum of `x` and `y`. No overflow occurs.
//!        If the sum is odd, the result is a rounded value at a distance guaranteed
//!        to be less than or equal to 0.5 of the mean_value floating value, but may differ
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
//!     6. The mean_value is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!        to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!        ensures generally faster computation, but strict inequality.
//!        For integral type entries, these are similar to `ceil((x+y)/2)`, but converted to an integral value.
//!     7. The mean_value is computed in a 'round toward \f$ +\infty\f$ mode. The result is guaranted
//!        to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!        ensures generally faster computation, but strict inequality.
//!        For integral type entries,  these are similar to `floor((x+y)/2)` but converted to an integral value.
//!     8. The mean_value is computed in the double sized element type (if available).
//!     9. Kahan like Compensated algorithm for better precision.
//!     10. Uses the Welford incremental algorithm.
//!     11. Uses incremental version of welford from a previously computed mean of n elements stored in
//!         `prevavg` and other new values
//!
//!  @note
//!     1.  with raw option is a spurious overflow can be obtained.
//!     2.  `mean`can be used as an alias to `mean_value`.
//!
//!
//!  @groupheader{External references}
//!   *  [Wikipedia Mean](https://en.wikipedia.org/wiki/Mean)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/mean_value.cpp}
//================================================================================================
  inline constexpr auto mean_value = functor<mean_value_t>;
//================================================================================================
//! @}
//================================================================================================

}
namespace eve::detail
{
  template<typename T0, typename ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  mean_value_(EVE_REQUIRES(cpu_), O const &, T0 a0, Ts const &... args) noexcept
  {
    if constexpr(sizeof...(Ts) == 0)
      return a0;
    else if constexpr(value<T0>)
    {
      using r_t =  common_value_t<T0,  Ts...>;
      auto wa0 = wf<r_t>(a0, 1u);
      return mean_value(wa0, args...);
    }
    else
    {
      using r_t =  common_value_t<typename T0::wf_t,  Ts...>;
      auto na0 = wf<r_t>(a0.avg_, a0.n_);
      auto doit = [&na0](auto... as){
        auto welfordstep = [&na0](auto a)
        {
          ++na0.n_;
          na0.avg_ += (a-na0.avg_)/na0.n_;
          return na0;
        };
        ((na0 = welfordstep(r_t(as))),...);
        return na0;
      };
      return  doit(args...);
    }
  }

  template<typename T0, typename T1, callable_options O>
  EVE_FORCEINLINE constexpr auto
  mean_value_(EVE_REQUIRES(cpu_), O const &, T0 na, T1 const & nb) noexcept
  requires(detail::is_wf<T0>::value && detail::is_wf<T1>::value)
  {
    using r_t =  common_value_t<typename T0::wf_t,  typename T1::wf_t>;
    auto nab = na.n_+nb.n_;
    return wf<r_t>(sum_of_prod(r_t(na.n_), na.avg_, r_t(nb.n_), nb.avg_), nab);
  }
}
