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
  struct covariance_t : callable<covariance_t, Options, kahan_option, widen_option, unbiased_option>
  {
    template<value Tup1, value Tup2>
    requires(eve::product_type<element_type_t<Tup1>> && eve::product_type<element_type_t<Tup2>> && Options::contains(widen))
    EVE_FORCEINLINE constexpr
    eve::upgrade_t<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(t1, t2); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::product_type<element_type_t<Tup1>> && eve::product_type<element_type_t<Tup2>> && !Options::contains(widen))
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(t1, t2); }

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
//!      constexpr auto covariance(kumi::non_empty_product_type xs, kumi::non_empty_product_type ys)            noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto covariance[kahan]   (/*any of the above overloads*/)                                    noexcept; // 2
//!      constexpr auto covariance[unbiased](/*any of the above overloads*/)                                    noexcept; // 3
//!      constexpr auto covariance[widen]   (/*any of the above overloads*/)                                    noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs`, `ys`  :  tuples of floating value arguments.
//!
//!    **Return value**
//!
//!    1. covariance product. \f$\frac1N\sum_s (x_s-\bar{x_s})*(y_s-\bar{y_s})\f$.
//!       where N is the number of `x_s` (minus 1 if `unbiased` option is used).
//!    2. Uses a compensated kahan-like algorithm to compute the result more accurately
//!    3. see 1.
//!    4. Uses the upgraded type for computations and result
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
    template<kumi::non_empty_product_type PT1, kumi::non_empty_product_type PT2, callable_options O>
    EVE_FORCEINLINE constexpr auto covariance_(EVE_REQUIRES(cpu_), O const & o, PT1 f, PT2 s) noexcept
    requires (kumi::as_tuple_t<PT1>::size() == kumi::as_tuple_t<PT2>::size())
    {
     if constexpr(O::contains(widen)) {
        auto up = [](auto tup){
          auto upg = [](auto t){return eve::upgrade(t); };
          return kumi::map(upg, tup);
        };
        return covariance[o.drop(widen)](up(f), up(s));
      }
     else
     {
       using Tup1 = kumi::as_tuple_t<PT1>;
       using Tup2 = kumi::as_tuple_t<PT2>;
       constexpr auto siz = Tup1::size();
       constexpr auto fac = O::contains(unbiased) ? siz-1 : siz;
       using r1_t = kumi::apply_traits_t<eve::common_value, Tup1>;
       using r2_t = kumi::apply_traits_t<eve::common_value, Tup2>;

       using r_t =  eve::common_value_t<r1_t, r2_t>;

       if constexpr(siz == 1)
         return eve::zero(eve::as<r_t>());
       else
       {
         auto avgf = eve::average[o](f);
         auto avgs = eve::average[o](s);
         if constexpr(O::contains(raw))
           auto cov = kumi::sum( kumi::map([avgf, avgs](auto a, auto b) { return (a-avgf)*(b-avgs); }, f, s))/fac;
         else
         {
           auto fc =  kumi::map([avgf](auto a) { return (a-avgf); }, f);
           auto sc =  kumi::map([avgs](auto a) { return (a-avgs); }, s);
           return eve::dot[o](fc, sc)/fac;
         }
       }
     }
    }
  }
}
