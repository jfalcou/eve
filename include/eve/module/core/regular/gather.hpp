//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct gather_t : callable<gather_t, Options, conditional_option>
  {
    template<integral_value T, typename U>
    constexpr EVE_FORCEINLINE auto operator()(U const* ptr, T v) const noexcept
    {
      return EVE_DISPATCH_CALL(ptr, v);
    }

    template<integral_value T, typename U, typename S>
    constexpr EVE_FORCEINLINE auto operator()(aligned_ptr<U, S> ptr, T v) const noexcept
    {
      return EVE_DISPATCH_CALL(ptr, v);
    }

    EVE_CALLABLE_OBJECT(gather_t, gather_);
  };

  // TODO DOC
  //================================================================================================
  //! @addtogroup core_simd
  //! @{
  //!   @var gather
  //!   @brief Computes the TODO
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
  //!      TODO
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `x`:  An instance of an [SIMD value](@ref eve::simd_value)
  //!
  //!    **Return value**
  //!
  //!      * TODO
  //!
  //!  @groupheader{Example}
  //!
  //!  TODO
  //================================================================================================
  inline constexpr auto gather = functor<gather_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/gather.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/gather.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/gather.hpp>
#endif
