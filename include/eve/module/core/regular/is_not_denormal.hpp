/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/bit_value.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_denormal_t : elementwise_callable<is_not_denormal_t, Options>
  {
    template<value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_not_denormal_t, is_not_denormal_);
  };

  //================================================================================================
  //! @addtogroup core_predicates
  //! @{
  //!   @var is_not_denormal
  //!   @brief `elementwise callable` returning a logical true if and only if the element value is not denormal.
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
  //!      constexpr auto is_not_denormal(floating_value auto x) noexcept;                 // 1
  //!      constexpr auto is_not_denormal(integral_value auto x) noexcept;                 // 2
  //!
  //!      // Lanes masking
  //!      constexpr auto is_not_denormal[conditional_expr auto c](value auto x) noexcept; // 3
  //!      constexpr auto is_not_denormal[logical_value auto m](value auto x) noexcept;    // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: [argument](@ref eve::value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. returns true if and only if `x` is not
  //!         [denormal](https://mathworld.wolfram.com/SubnormalNumber.html).
  //!     2. always return `true`.
  //!     3. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/is_not_denormal.cpp}
  //================================================================================================
  inline constexpr auto is_not_denormal = functor<is_not_denormal_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T> is_not_denormal_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr (!floating_value<T> || !eve::platform::supports_denormals)
        return true_(as<T>{});
      else
        return is_eqz(a) || is_not_less(eve::abs(a), smallestposval(as<T>{}));
    }
  }
}
