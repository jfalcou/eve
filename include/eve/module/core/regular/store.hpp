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
  struct store_t : relative_conditional_callable<store_t, Options>
  {
    template<simd_value T, simd_compatible_ptr<T> Ptr>
    EVE_FORCEINLINE void operator()(T value, Ptr ptr) const noexcept
    {
      return EVE_DISPATCH_CALL(value, ptr);
    }

    EVE_CALLABLE_OBJECT(store_t, store_);
  };

  //================================================================================================
  //! @addtogroup memory
  //! @{
  //!   @var store
  //!   @brief Store the elements of a [SIMD value](@ref eve::simd_value) into the given memory
  //!          location.
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
  //!     // Regular overload
  //!     template<simd_value T, simd_compatible_ptr<T> Ptr>
  //!     void store(T value, Ptr ptr) noexcept;                                         // 1
  //!
  //!     // Lanes masking
  //!     auto mul[conditional_expr auto c](/* any of the above overloads */) noexcept;  // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!    * `value` : The [SIMD value](@ref eve::simd_value) to store.
  //!    * `ptr`   : A pointer to the memory location where the elements of `value` will be stored.
  //!    * `c`     : A [relative conditional expression](@ref eve::relativeconditional_expr) masking
  //!                the operation.
  //!
  //!   **Overloads**
  //!
  //!    1. Stores the elements of `value` into the memory location pointed to by `ptr`.
  //!    2. Same as 1. but lanes masked by the condition `c` will not be stored.
  //!
  //================================================================================================
  inline constexpr auto store = functor<store_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/store.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/store.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/store.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/store.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/store.hpp>
#endif

// #if defined(EVE_INCLUDE_RISCV_HEADER)
// #  include <eve/module/core/regular/impl/simd/riscv/store.hpp>
// #endif
