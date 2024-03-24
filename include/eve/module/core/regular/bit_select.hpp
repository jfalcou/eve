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
#include <eve/module/core/regular/bit_shl.hpp>

namespace eve
{
  template<typename Options>
  struct bit_select_t : elementwise_callable<bit_select_t, Options>
  {
    template<eve::value M, value T, value U>
    constexpr EVE_FORCEINLINE bit_value_t<T, U, M>
    operator()(M m, T u, U v) const
    { return EVE_DISPATCH_CALL(m, u, v); }

    EVE_CALLABLE_OBJECT(bit_select_t, bit_select_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_select
//!   @brief selects bits from a mask and two entries.
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
//!     template< value T, value U > U bit_select)( T m, U x, U y )
//!      noexcept;
//!   }
//!   @endcode
//!
//!
//!   **Parameters**
//!
//!   * `m`:   mask [value](@ref eve::value)
//!
//!   * `y`, `z`:   selection [values](@ref eve::value)
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      * In a short way (omitting casting details to bring all bit sizes of the parameters equal),
//!      it means that the result is
//!        composed of the bits of `x` for which the corresponding bit of `m` is set
//!        and the bits of  `y` for which the corresponding bit of `m` is unset.
//!
//!      * If `T` or `U` is an [simd value](@ref eve::simd_value), the type of the result has the
//!      element type
//!        of `T` and the maximum of the cardinals of `M` and `T`, otherwise it is `T`.
//!        The value of the selected bits is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_select.cpp}
//!
//!  @}
//================================================================================================
  inline constexpr auto bit_select = functor<bit_select_t>;
namespace tag
{
  struct bit_select_;
}
template<> struct supports_conditional<tag::bit_select_> : std::false_type
{};

}

#include <eve/module/core/regular/impl/bit_select.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_select.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_select.hpp>
#endif
