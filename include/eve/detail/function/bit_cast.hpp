//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/spy.hpp>
#include <eve/as.hpp>
#include <cstring>

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var bit_cast
  //!
  //! @brief Callable object computing a bitwise reinterpretation of the object.
  //!
  //! **Required header:** `#include <eve/function/bit_cast.hpp>`
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

namespace eve::detail
{
  template<typename T, typename Target>
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(cpu_), T const &a, as<Target> const &) noexcept
  requires (sizeof(T) == sizeof(Target))
  {
    if constexpr(std::is_same_v<T, Target>)
    {
      return a;
    }
    else
    {
      [[maybe_unused]] Target that;
      std::memcpy((char*)&that, (char*)&a, sizeof(a));
      return that;
    }
  }
}

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic pop
#endif
