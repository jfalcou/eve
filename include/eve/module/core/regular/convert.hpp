//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //!   @var convert
  //!   @brief Converts a value to another type.
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
  //!      template<value T, scalar_value Target>
  //!      Target convert( T x, as_<Target> t)  noexcept
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`:   [value](@ref eve::value) to convert.
  //!
  //!     * `t`:   [Type wrapper](@ref eve::as) instance embedding the type to convert `x` to.
  //!
  //!    **Return value**
  //!
  //!      * conversion of `x` is the `Target` type is returned.
  //!
  //!      * The call `convert(x, as(t))` is semantically equivalent to:
  //!
  //!        @code
  //!        Target r;
  //!
  //!        if constexpr( scalar_value<T> )
  //!        {
  //!          r = static_cast<Target>(x);
  //!        }
  //!        else if constexpr( simd_value<T> )
  //!        {
  //!           for(std::size_t i=;i<x.size();++i)
  //!           r[i] = static_cast<Target>(x[i]);
  //!        }
  //!        @endcode
  //!
  //!      *  Conversion operated by [eve::convert](#eve::convert) follows the regular rules of
  //!         C++ type conversion, including the cases leading to Undefined Behaviors.
  //!
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/convert.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * eve::saturated
  //!
  //!     The expression `saturated(convert)(x,t)` computes a saturated conversion of `x` to
  //!     the type wrapped by `t`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/saturated/convert.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(convert_, convert);
}

#include <eve/module/core/regular/impl/convert.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/convert.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/convert.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/convert.hpp>
#endif
