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
#include <eve/module/core/regular/is_finite.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fms.hpp>
#include <eve/module/core/regular/fnma.hpp>

namespace eve
{
  template<typename Options>
  struct sum_of_prod_t : elementwise_callable<sum_of_prod_t, Options, raw_option, pedantic_option, lower_option,
                                upper_option, strict_option>
  {
    template<value T,  value U, value V,  value W>
    requires(eve::same_lanes_or_scalar<T, U, V, W>)
    constexpr EVE_FORCEINLINE common_value_t<T, U, V, W> operator()(T a, U b, V c, W d) const
    { return EVE_DISPATCH_CALL(a, b, c, d); }

    EVE_CALLABLE_OBJECT(sum_of_prod_t, sum_of_prod_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var sum_of_prod
//!   @brief `elementwise_callable` object computing the sum of products operation with better accuracy
//!   than the naive formula.
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
//!      // Regular overload
//!      constexpr auto sum_of_prod(floating_value auto x, floating_value auto y,
//!                                 floating_value auto z, floating_value auto t)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sum_of_prod[conditional_expr auto c](floating_value auto x, floating_value auto y,
//!                                                          floating_value auto z, floating_value auto t) noexcept; // 2
//!
//!      // Semantic exclusive options
//!      constexpr auto sum_of_prod[raw](floating_value auto x, floating_value auto y,
//!                                      floating_value auto z, floating_value auto t)                     noexcept; // 3
//!      constexpr auto sum_of_prod[pedantic](floating_value auto x, floating_value auto y,
//!                                           floating_value auto z, floating_value auto t)                noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`, `t`:  [floating value arguments](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of `x*y-z*t`,  with better precision if correct fma is available, is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. computes a raw  version of sum_of_prod,  i.e. the naive formula (in fact  `fma(x, y, z*t)`)
//!      4. computes a pedantic version of `diff_of_prod` ensuring better accuracy in any case.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sum_of_prod.cpp}
//================================================================================================
  inline constexpr auto sum_of_prod = functor<sum_of_prod_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    sum_of_prod_(EVE_REQUIRES(cpu_), O const & o,
                  T const &a,  T const &b,
                  T const &c,  T const &d) noexcept
    {
      if constexpr(O::contains(raw))
      {
        T cd =  mul(c, d);
        return fma(a, b, cd);
      }
      else if constexpr(floating_value<T> && (O::contains(lower) || O::contains(upper) ))
      {
        if constexpr(O::contains(strict))
        {
          auto r = sum_of_prod[o.drop(lower, upper, strict)](a, b, c, d);
          if constexpr(O::contains(lower))
            return prev(r);
          else
            return next(r);
        }
        else
        {
          T cdl =  mul[lower](c, d);
          T cdu =  mul[upper](c, d);
          if constexpr(O::contains(upper))
          {
            auto err = fms[o](c, d, cdl);
            auto dop = fma[o](a, b, cdu);
            return add[o][is_finite(err)](dop, err);
          }
          else
          {
            auto err = fms[o](c, d, cdu);
            auto dop = fma[o](a, b, cdl);
            return add[o][is_finite(err)](dop, err);
          }
        }
      }
      else
      {
        T cd =  mul[o](c, d);
        auto err = fms[o](c, d, cd);
        auto dop = fma[o](a, b, cd);
        return add[o][is_finite(err)](dop, err);
      }
    }
  }
}
