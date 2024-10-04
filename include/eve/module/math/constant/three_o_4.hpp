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
  struct three_o_4_t : constant_callable<three_o_4_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.8p-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.8p-1};
        else                                      return T{0x1.8p-1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.8p-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.8p-1};
        else                                      return T{0x1.8p-1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(three_o_4_t, three_o_4_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var three_o_4
  //!   @brief Callable object computing the constant \f$3/4\f$.
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
  //!      T three_o_4(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::three_o_4(as<T>())` returns  \f$3/4\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/three_o_4.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto three_o_4 = functor<three_o_4_t>;
}
