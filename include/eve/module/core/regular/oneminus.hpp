//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve
{
  template<typename Options>
  struct oneminus_t : elementwise_callable<oneminus_t, Options, saturated_option, lower_option,
                                           upper_option, strict_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), a);
    }

    EVE_CALLABLE_OBJECT(oneminus_t, oneminus_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var oneminus
//!   @brief `elementwise_callable` computing the value of one minus the input.
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
//!      constexpr auto oneminus(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto oneminus[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto oneminus[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto oneminus[saturated ](value auto x)              noexcept; // 3
//!      constexpr auto oneminus[lower](value auto x)                   noexcept; // 4
//!      constexpr auto oneminus[upper](value auto x)                   noexcept; // 5
//!      constexpr auto oneminus[lower][strict](value auto x)           noexcept; // 4
//!      constexpr auto oneminus[upper][strict](value auto x)           noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [real](@ref eve::value) argument.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of `1-x` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. saturated version.
//!      4. The operation is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!         to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!      5. The operation is computed  in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!         to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!
//!    @note
//!      If an  [element](@ref glossary_elementwise) of the expected result is not representable in
//!      the result type, the corresponding result [element](@ref glossary_elementwise) is
//!      undefined.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/oneminus.cpp}
//================================================================================================
  inline constexpr auto oneminus = functor<oneminus_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr T
    oneminus_(EVE_REQUIRES(cpu_), O const& o, T v) noexcept
    {
      using elt_t = element_type_t<T>;
      if constexpr( std::is_floating_point_v<elt_t> || !O::contains(saturated) )
      {
        return add[o](one(as<T>{}), minus(v));
      }
      else
      {
        if constexpr( std::is_unsigned_v<elt_t> )
        {
          return one[is_eqz(v)](as{v});
        }
        else if constexpr( scalar_value<T> )
        {
          return (v <= valmin(eve::as{v}) + 2) ? valmax(eve::as{v}) : oneminus(v);
        }
        else if constexpr( simd_value<T> )
        {
          return if_else(v < valmin(eve::as{v}) + 2, valmax(eve::as{v}), oneminus(v));
        }
      }
    }
  }
}
