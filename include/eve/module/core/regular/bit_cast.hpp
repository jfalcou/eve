/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if defined(EVE_DOXYGEN_INVOKED)
#include <eve/traits/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_bitops
  //! @{
  //!   @var bit_cast
  //!   @brief Computes a a bitwise reinterpretation of an object.
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
  //!       template<value From, scalar_value To>
  //!       To bit_cast operator()(From x, as<To> t) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!     * `t` :  [Type wrapper](@ref eve::as) instance embedding the type of the result.
  //!
  //!  **Template parameters**
  //!
  //!     * To: scalar type to which each element of `x` is casted
  //!
  //!    **Return value**
  //!
  //!    The bits of x of type From reinterpreted as being those of a variable of type To
  //!    is returned.
  //!
  //!    Every bit in the value representation of the returned To object is equal to the
  //!    corresponding bit in the object representation of from.
  //!    The values of padding bits in the returned To object are unspecified.
  //!
  //!    If there is no value of type To corresponding to the value
  //!    representation produced, the behavior is undefined. If there are multiple
  //!    such values, which value is produced is unspecified.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/bit_cast.cpp}
  //!
  //! @}
  //================================================================================================
  inline constexpr auto bit_cast = functor<bit_cast_t>;
}
#endif

#include <eve/detail/function/bit_cast.hpp>
