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

namespace eve
{
  template<typename Options>
  struct mul_t : tuple_callable<mul_t, Options, saturated_option>
  {
    template<eve::value T0, value T1, value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(mul_t, mul_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var mul
//!   @brief Computes the sum of its arguments.
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
//!      template< eve::value... Ts >
//!      eve::common_value_t<Ts ...> mul(Ts ... x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `... xs` : [real](@ref eve::value) arguments.
//!
//!    **Return value**
//!
//!    The value of the product of the arguments is returned.
//!
//!   @note
//!     Take care that for floating entries, the multiplication is only 'almost' associative.
//!     This call performs multiplications in reverse incoming order.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/mul.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::mul[mask](x, ...)` provides a masked
//!     version of `mul` which is
//!     equivalent to `if_else(mask, mul(x, ...), x)`
//!
//!   * eve::saturated
//!
//!     The call `mul[saturated](args...)` computes the saturated  multiplication `of the arguments.
//!     The saturation is obtained in the [common value](@ref common_value_t)
//!     of the N parameters. The computation is done as if all arguments were
//!     converted to this type and the saturated multiplication applied recursively on all
//!     parameters. No overflow occurs.
//!
//! @}
//================================================================================================
  inline constexpr auto mul = functor<mul_t>;

  // Required for optimisation detections
  using callable_mul_ = tag_t<mul>;
}

#include <eve/module/core/regular/impl/mul.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/mul.hpp>
#endif


#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/mul.hpp>
#endif
