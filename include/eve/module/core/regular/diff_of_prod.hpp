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
  struct diff_of_prod_t : elementwise_callable<diff_of_prod_t, Options, raw_option, pedantic_option, lower_option,
                                upper_option, strict_option>
  {
    template<value T, value U, value V, value W>
    constexpr EVE_FORCEINLINE common_value_t<T, U, V, W> operator()(T a, U b, V c, W d) const
      requires(eve::same_lanes_or_scalar<T, U, V, W>)
    {
      return this->behavior(as<common_value_t<T, U, V, W>>{}, eve::current_api, this->options(), a, b, c, d);
    }

    EVE_CALLABLE_OBJECT(diff_of_prod_t, diff_of_prod_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var diff_of_prod
//!   @brief `elementwise_callable` object computing the difference of products operation with better accuracy
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
//!      constexpr auto diff_of_prod(floating_value auto x, floating_value auto y,
//!                                  floating_value auto z, floating_value auto t)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto diff_of_prod[conditional_expr auto c](floating_value auto x, floating_value auto y,
//!                                                           floating_value auto z, floating_value auto t) noexcept; // 2
//!
//!      // Semantic exclusive options
//!      constexpr auto diff_of_prod[raw](floating_value auto x, floating_value auto y,
//!                                       floating_value auto z, floating_value auto t)                     noexcept; // 3
//!      constexpr auto diff_of_prod[pedantic](floating_value auto x, floating_value auto y,
//!                                            floating_value auto z, floating_value auto t)                noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`, `t`:  [floating values](@ref floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of `x*y-z*t`,  with better precision if correct fma is available,
//!        is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. computes a raw  version of diff_of_prod,  i.e. the naive formula (in fact  `fms(x, y, z*t)`)
//!      4. computes a pedantic version of `diff_of_prod` ensuring better accuracy in any case.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/diff_of_prod.cpp}
//================================================================================================
 inline constexpr auto diff_of_prod = functor<diff_of_prod_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr auto
    diff_of_prod_(EVE_REQUIRES(cpu_), O const& o,
                  T const &a,  T const &b,
                  T const &c,  T const &d) noexcept
    {
      if constexpr(O::contains(raw))
      {
       T cd =  mul(c, d);
       return fms(a, b, cd);
      }
      else if constexpr(floating_value<T> && (O::contains(lower) || O::contains(upper) ))
      {
        if constexpr(O::contains(strict))
        {
          auto r = diff_of_prod[o.drop(lower, upper, strict)](a, b, c, d);
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
            auto err = fnma[o](c, d, cdu);
            auto dop = fms[o](a, b, cdl);
            return add[o][is_finite(err)](dop, err);
          }
          else
          {
            auto err = fnma[o](c, d, cdl);
            auto dop = fms[o](a, b, cdu);
            return add[o][is_finite(err)](dop, err);
          }
        }
      }
      else
      {
        auto cd = mul[o](c, d);
        auto err = fnma[o](c, d, cd);
        auto dop = fms[o](a, b, cd);
        return add[o][is_finite(err)](dop, err);
      }
    }
  }
}
