//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var bit_select
  //!
  //! @brief Callable object computing the bit_select operation.
  //!
  //! **Required header:** `#include <eve/function/bit_select.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the bit_select operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T m, U x, U y ) const noexcept
  //!  requires compatible< T,U>;
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`m`:   mask [value](@ref eve::value)
  //!
  //!`y`, `z`:   selection [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!The types T and U must be  bit_compatible and the call
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!r==bit_select(m,x,y)
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically equivalent to
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!r = bit_or(bit_and(x, m), bit_andnot(y, m))
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!In a short way (omitting casting details to bring all bit sizes of the parameters equal), it means that the result is
  //!composed of the bits of `x` for which the corresponding bit of `m` is set
  //!and the bits of  `y` for which the corresponding bit of `m` is unset.
  //!
  //!If `T` or `U` is an [simd value](@ref eve::simd_value), the type of the result has the element type
  //! of `T` and the maximum of the cardinals of `M` and `T`, otherwise it is `T`.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/bit_select.cpp
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct bit_select_; }
  template<> struct supports_conditional<tag::bit_select_> : std::false_type {};

  EVE_MAKE_CALLABLE(bit_select_, bit_select);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/bit_select.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/bit_select.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/bit_select.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/bit_select.hpp>
#endif
