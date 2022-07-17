/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#if defined(EVE_DOXYGEN_INVOKED)
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var bit_cast
  //!
  //! @brief Callable object computing a bitwise reinterpretation of the object.
  //!
  //! **Required header:** `#include <eve/module/core/regular/bit_cast.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Obtain a value of type To by reinterpreting the object representation of from  |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<real_value From, scalar_real_value To>
  //!  auto operator()(From x, as<To> t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! @param
  //! x: instance of a [value](@ref eve::value) to be casted
  //!
  //! @tparam
  //! To: [value] to which `x` is casted
  //!
  //! **Return value**
  //!
  //!Obtain a value of type To by reinterpreting the object representation
  //!of from. Every bit in the value representation of the returned To object is
  //!equal to the corresponding bit in the object representation of from.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/bit_cast.cpp}
  //!
  //!  @}
  //================================================================================================z
  EVE_MAKE_CALLABLE(bit_cast_, bit_cast);
}
#endif

#include <eve/detail/function/bit_cast.hpp>
