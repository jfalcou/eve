//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/pattern.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_simd
  //! @{
  //!   @var broadcast
  //!   @brief Computes the
  //!
  //!   $details$
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
  //!      template< eve::value T >
  //!      T broadcast(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `x`:  An instance of an [SIMD value](@ref eve::simd_value)
  //!
  //!      * `i`:  An eve::index indicating which lane of `x` to broadcast
  //!
  //!    **Return value**
  //!
  //!      *  If `x` is an instance of an [SIMD value](@ref eve::simd_value) `T`, the call is equivalent to `T{x.get(I)}`.
  //!      *  If `x` is an instance of a [scalar value](@ref eve::scalar_value) the call simply returns `x`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/broadcast.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(broadcast_, broadcast);
}

#include <eve/module/core/regular/impl/broadcast.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/broadcast.hpp>
#endif
