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
  struct add_t : tuple_callable<add_t, Options, saturated_option>
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

    EVE_CALLABLE_OBJECT(add_t, add_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var add
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
//!      template<eve::value... Ts >
//!      eve::common_value_t<Ts ...> add(Ts ... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` :  [Values](@ref eve::value) to sum.
//!
//!   **Return value**
//!
//!     The value of the sum of the arguments.
//!
//!   @note
//!
//!     * Take care that for floating entries, the addition is only 'almost' associative.
//!       This call performs additions in reverse incoming order.
//!
//!     * Although the infix notation with `+` is supported for two parameters, the `+` operator on
//!       standard scalar types is the original one and so can lead to automatic promotion.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/add.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::add[mask](x, ...)` provides a masked
//!     version of `add` which is equivalent to `if_else(mask, eve::add(x, ...), x)`
//!
//!   * eve::saturated
//!
//!     The call `eve::add[eve::saturated](...)` computes a saturated version of `eve::add`.
//!
//!     Take care that for signed integral entries this kind of addition is not associative at all.
//!     This call perform saturated additions in reverse incoming order.
//! @}
//================================================================================================
  inline constexpr auto add = functor<add_t>;

  // Required for optimisation detections
  using callable_add_ = tag_t<add>;
}

#include <eve/module/core/regular/impl/add.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/add.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/add.hpp>
#endif
