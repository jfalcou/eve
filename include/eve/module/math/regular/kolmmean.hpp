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
#include <eve/module/core.hpp>
#include <eve/module/math/regular/pow_abs.hpp>

namespace eve
{
  template<typename Options>
  struct kolmmean_t : callable<kolmmean_t, Options, pedantic_option, widen_option,
                                     kahan_option>
  {
    template<typename F, typename G,  value... Ts>
    requires(!value<F> && sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<Ts...>)
      EVE_FORCEINLINE constexpr eve::upgrade_if_t<Options, common_value_t<Ts...>>
    operator()(F f, G g, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(f, g, ts...); }

    template<typename F, typename G, kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    eve::upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(F f, G g, Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(f, g, t); }


    EVE_CALLABLE_OBJECT(kolmmean_t, kolmmean_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var kolmmean
//!
//! @brief Callable object computing the 'Kolmogorov-Nagumo-de Finetti' mean of the inputs: \f$ \mathbf{g}(\sum \mathbf{f}(x_s)) \f$.
//!
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto kolmmean(floating_value auto ... xs)                               noexcept; // 1
//!      constexpr auto kolmmean(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto kolmmean[kahan](/*any of the above overloads*/)                    noexcept; // 4
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `f`, `g`: two functions that will be used to compute the mean.
//!    * `xs`: [real](@ref eve::value) arguments.
//!    * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. The kolmogorov mean of the inputs is returned
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!    4. uses kahan like compensated algorithm for better accuracy.
//!
//!  @note For the result to be a proper kolmogorov mean, `f` must be mathematically continuous and injective and `g` be its inverse.
//!        and **EVE** need them to be defined for a floating_value input, and returning the same type.
//!        However \f$ \mathbf{g}(\sum \mathbf{f}(x_s)) \f$ is returned if computable.
//!
//!  @groupheader{External references}
//!   *  [wikipedia quasi-arithmetic mean](https://en.wikipedia.org/wiki/Quasi-arithmetic_mean)

//!  @groupheader{Example}
//!  @godbolt{doc/math/kolmmean.cpp}
//================================================================================================
  inline constexpr auto kolmmean = functor<kolmmean_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename F, typename G, floating_value... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    kolmmean_(EVE_REQUIRES(cpu_), O const & o, F f, G g, Ts... args) noexcept
    {
      constexpr auto sz = sizeof...(Ts);
      if constexpr(O::contains(widen))
        return kolmmean[o.drop(widen)](f, g, upgrade(args)...);
      else if constexpr(sz == 1)
        return ((args), ...);
      else
      {
        return g(average[o](f(args)...));
      }
    }

    template<typename F, typename G, kumi::non_empty_product_type Tup, callable_options O>
    EVE_FORCEINLINE constexpr auto
    kolmmean_(EVE_REQUIRES(cpu_), O const & o, F f, G g, Tup t) noexcept
    {
      return kumi::apply([f, g, o](auto ...m){return kolmmean[o](f, g, m...); }, t);
    }
  }
}
