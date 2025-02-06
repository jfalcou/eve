//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct scan_t : callable<scan_t, Options>
  {
    template<simd_value Wide, typename Op, typename Zero>
    constexpr EVE_FORCEINLINE Wide operator()(Wide w, Op op, Zero z) const noexcept
    {
      return EVE_DISPATCH_CALL(w, op, z);
    }

    template<simd_value Wide>
    constexpr EVE_FORCEINLINE Wide operator()(Wide w) const noexcept
    {
      return EVE_DISPATCH_CALL(w, add, eve::zero);
    }

    EVE_CALLABLE_OBJECT(scan_t, scan_);
  };

  //TODO DOC
  //================================================================================================
  //! @addtogroup core_simd
  //! @{
  //!   @var scan
  //!   @brief TODO
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
  //!     constexpr simd_value scan(simd_value auto x, auto op, auto zero) noexcept; // 1
  //!     constexpr simd_value scan(simd_value auto x) noexcept;                     // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `x`:  An instance of an [SIMD value](@ref eve::simd_value)
  //!
  //!    **Return value**
  //!
  //!      1. TODO
  //!      2. TODO
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/scan.cpp}
  //!
  //================================================================================================
  inline constexpr auto scan = functor<scan_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/scan.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/scan.hpp>
#endif
