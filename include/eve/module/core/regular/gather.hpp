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
  struct gather_t : conditional_callable<gather_t, Options>
  {
    template<arithmetic_value T, integral_value U>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, U> operator()(T const* ptr, U idx) const noexcept
    {
      return EVE_DISPATCH_CALL(ptr, idx);
    }

    template<arithmetic_value T, integral_value U, typename N>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, U> operator()(aligned_ptr<T, N> ptr, U idx) const noexcept
    {
      return EVE_DISPATCH_CALL(ptr, idx);
    }

    EVE_CALLABLE_OBJECT(gather_t, gather_);
  };

  //================================================================================================
  //! @addtogroup core_simd
  //! @{
  //!   @var gather
  //!   @brief Load a SIMD value with values selected from a memory region at the given offsets.
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
  //!     template<arithmetic_value T, integral_value U>
  //!     as_wide_as_t<T, U> gather(T const* ptr, U idx);
  //!
  //!     template<arithmetic_value T, integral_value U, typename N>
  //!     auto gather(aligned_ptr<T, N> ptr, U idx);
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `idx`: An instance of an [integral value](@ref eve::integral_value).
  //!      * `ptr`: A pointer to the memory region to load from.
  //!
  //!    **Return value**
  //!
  //!      * A [value](@ref eve::value) equivalent to: 
  //!        @code
  //!        as_wide_as_t<T, U> res = { ptr[idx[0]], ptr[idx[1]], ..., ptr[idx[N-1]] };
  //!        @endcode
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/gather.cpp}
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
