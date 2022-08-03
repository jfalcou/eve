//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/arch.hpp>

namespace eve
{
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
  //!   {   template< value T, value U > bit_select)( T m, U x, U y )
  //!       requires compatible< T,U> noexcept;
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
  //!      * In a short way (omitting casting details to bring all bit sizes of the parameters equal), it means that the result is
  //!        composed of the bits of `x` for which the corresponding bit of `m` is set
  //!        and the bits of  `y` for which the corresponding bit of `m` is unset.
  //!
  //!      * If `T` or `U` is an [simd value](@ref eve::simd_value), the type of the result has the element type
  //!        of `T` and the maximum of the cardinals of `M` and `T`, otherwise it is `T`.
  //!        The value of the selected bits is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/bit_select.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct bit_select_; }
  template<> struct supports_conditional<tag::bit_select_> : std::false_type {};

  EVE_MAKE_CALLABLE(bit_select_, bit_select);
}

#include <eve/module/core/regular/impl/bit_select.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_select.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_select.hpp>
#endif
