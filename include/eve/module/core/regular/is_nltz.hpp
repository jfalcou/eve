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
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_not_less.hpp>
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  template<typename Options>
  struct is_nltz_t : elementwise_callable<is_nltz_t, Options>
  {
    template<value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_nltz_t, is_nltz_);
  };

  //================================================================================================
  //! @addtogroup core_predicates
  //! @{
  //!   @var is_nltz
  //!   @brief `elementwise callable` returning a logical true  if and only if the element value is not less than zero.
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
  //!      constexpr auto is_nltz(value auto x) noexcept;                          // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto is_nltz[conditional_expr auto c](value auto x) noexcept; // 2
  //!      constexpr auto is_nltz[logical_value auto m](value auto x) noexcept;    // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`:  [argument](@ref eve::value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. `is_nltz(x)` is semantically equivalent to `!(x < 0)`.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!   @note This is not equivalent to `(x >= 0)` for floating values because of `NaN` properties..
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/is_nltz.cpp}
  //================================================================================================
  inline constexpr auto is_nltz = functor<is_nltz_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T> is_nltz_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr (unsigned_value<T>)
        return true_(eve::as{a});
      else
      {
        if constexpr (scalar_value<T>)
        {
          if      constexpr (integral_value<T>) return is_gez(a);
          else if constexpr (floating_value<T>) return is_gez(a) || is_nan(a);
        }
        else
          return is_not_less(a, zero(as{a}));
      }
    }
  }
}
