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
  struct sub_t : tuple_callable<sub_t, Options, saturated_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(sub_t, sub_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sub
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
//!      template< eve::value... Ts>
//!      eve::common_value_t<Ts ...> sub(Ts ... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `... xs` :  [real](@ref eve::value) arguments.
//!
//!    **Return value**
//!
//!      If the arguments are \f$(x_i)_{0\le i\le n}\f$ The value of \f$x_0-\sum_1^n x_i\f$
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/sub.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::sub[mask](x, ...)` provides a masked
//!     version of `sub` which is
//!     equivalent to `if_else(mask, sub(x, ...), x)`
//!
//!   * eve::saturated
//!
//!     The call `eve::saturated(eve::sub)(...)` computes
//!     a saturated version of `eve::sub`.
//!
//!     Take care that for signed integral
//!     entries this kind of operation is highly order dependant. We do not advise
//!     to use it for more than 2 parameters.
//!
//! @}
//================================================================================================
  inline constexpr auto sub = functor<sub_t>;

}

#include <eve/module/core/regular/impl/sub.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sub.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/sub.hpp>
#endif
