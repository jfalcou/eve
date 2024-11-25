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
#include <eve/forward.hpp>
#include <eve/module/core/regular/countl_zero.hpp>

namespace eve
{
  template<typename Options>
  struct bit_width_t : elementwise_callable<bit_width_t, Options>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(bit_width_t, bit_width_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_width
//!   @brief  `elementwise_callable` object Computing elementwise the number of bits needed
//!   to store the parameter.
//!
//!   **Defined in Header**
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
//!      constexpr auto bit_width(unsigned_value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_width[conditional_expr auto c](unsigned_value auto x) noexcept; // 2
//!      constexpr auto bit_width[logical_value auto m](unsigned_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [unsigned argument](@ref eve::unsigned_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!      1. The value of  number of bits needed to store the value `x`,
//!        i.e. \f$1+\lfloor\log2(x)\rfloor\f$ is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_width.cpp}
//================================================================================================
  inline constexpr auto bit_width = functor<bit_width_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, unsigned_value T>
    constexpr T  bit_width_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      using elt_t = element_type_t<T>;
      return sizeof(elt_t) * 8 - countl_zero(v);
    }
  }
}
