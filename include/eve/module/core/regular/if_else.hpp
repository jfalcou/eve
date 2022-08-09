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
//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var if_else
//!   @brief Computes the results of a choice under condition
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
//!      template< eve::value T, eve::value U, eve::value V >
//!      auto if_else(T x, U, y, V z ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: condition
//!     * `y`, `z`:  choice [arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!      The call `if_else(x, y, z)` performs [elementwise](@ref glossary_elementwise)
//!      a choice between the elements of `y` and `z`
//!      according to the truth value of the elements of `x`.
//!
//!   **Possible optimizations**
//!
//!     The following calls where `x`, `y` and `z` are values can be optimized:
//!
//!        * `if_else(x, y, allbits< T >()) ` writing: `if_else(x, y, eve::allbits_)`
//!        * `if_else(x, y, one< T >()    ) ` writing: `if_else(x, y, eve::one_    )`
//!        * `if_else(x, y, mone< T >()   ) ` writing: `if_else(x, y, eve::mone_   )`
//!        * `if_else(x, y, zero< T >()   ) ` writing: `if_else(x, y, eve::zero_   )`
//!        * `if_else(x, allbits< T >(), z) ` writing: `if_else(x, eve::allbits_, z)`
//!        * `if_else(x, one< T >(), z    ) ` writing: `if_else(x, eve::one_, z    )`
//!        * `if_else(x, mone< T >(), z   ) ` writing: `if_else(x, eve::mone_, z   )`
//!        * `if_else(x, zero< T >(), z   ) ` writing: `if_else(x, eve::zero_, z   )`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/if_else.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(if_else_, if_else);
}

#include <eve/module/core/regular/impl/if_else.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/if_else.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/if_else.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/if_else.hpp>
#endif
