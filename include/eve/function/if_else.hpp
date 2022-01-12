//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup logical
  //! @{
  //! @var if_else
  //!
  //! @brief Callable object computing the if_else operation.
  //!
  //! **Required header:** `#include <eve/function/if_else.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the if_else operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U, value V > auto operator()( T x, U y, V z ) const noexcept
  //!  requires  compatible< U, V >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [values](@ref eve::value)
  //!
  //! **Return value**
  //!
  //!The call `if_else(x, y, z)` performs a choice between the elements of `y` and `z` according to the truth value
  //!of the elements of `x`.
  //!
  //!Let `UV` be the compatibility result of `U` and `V`.
  //!The call `auto r = if_else(x, y, z)` is semantically equivalent to:
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  if constexpr(scalar_value< T >)
  //!  {
  //!    return x ? UV(y) : UV(z);
  //!  }
  //!  else if constexpr(scalar_value< U > && scalar_value< V >)
  //!  {
  //!    for(int i=0; i < cardinal_v< T >; ++i)
  //!    {
  //!      r[i] = xx[i] ? y : z;
  //!    }
  //!  }
  //!  else
  //!  {
  //!    using C = wide< element_t< T >, cardinal_t< UV >>;
  //!    auto xx = C(x);
  //!    UV r;
  //!    for(int i=0; i<cardinal_v< UV >; ++i)
  //!    {
  //!      r[i] = xx[i] ? y[i] : z[i];
  //!    }
  //!  }
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  if `U`, `V` and `T` are scalar or if `U` or `V` are simd_values the result is of type `UV`,
  //!  otherwise it is of type  `wide< UV, cardinal_t< T >>`.
  //!
  //! #### Possible optimizations
  //!
  //! The following calls where `x`, `y` and `z` are values can be optimized:
  //!
  //!   * `if_else(x, y, allbits< T >()) ` writing: `if_else(x, y, eve::allbits_)`
  //!   * `if_else(x, y, one< T >()    ) ` writing: `if_else(x, y, eve::one_    )`
  //!   * `if_else(x, y, mone< T >()   ) ` writing: `if_else(x, y, eve::mone_   )`
  //!   * `if_else(x, y, zero< T >()   ) ` writing: `if_else(x, y, eve::zero_   )`
  //!   * `if_else(x, allbits< T >(), z) ` writing: `if_else(x, eve::allbits_, z)`
  //!   * `if_else(x, one< T >(), z    ) ` writing: `if_else(x, eve::one_, z    )`
  //!   * `if_else(x, mone< T >(), z   ) ` writing: `if_else(x, eve::mone_, z   )`
  //!   * `if_else(x, zero< T >(), z   ) ` writing: `if_else(x, eve::zero_, z   )`
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/if_else.cpp}
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(if_else_, if_else);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/if_else.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/if_else.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/if_else.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/if_else.hpp>
#endif
