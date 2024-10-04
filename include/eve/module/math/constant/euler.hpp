//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct euler_t : constant_callable<euler_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if constexpr (Opts::contains(upper)) return T{0x1.5bf0aap+1};
        if constexpr (Opts::contains(lower)) return T{0x1.5bf0a8p+1};
        else                                 return T{0x1.5bf0a8p+1};
      }
      else
      {
        if constexpr (Opts::contains(upper)) return T{0x1.5bf0a8b14576ap+1};
        if constexpr (Opts::contains(lower)) return T{0x1.5bf0a8b145769p+1};
        else                                 return T{0x1.5bf0a8b145769p+1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(euler_t, euler_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var euler
  //!   @brief Callable object computing the constant e basis of the natural logarithms.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::floating_value T >
  //!      T euler(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::euler(as<T>())` returns  the basis of the natural logarithms.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/euler.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto euler = functor<euler_t>;
}
