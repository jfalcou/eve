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
#include <eve/module/core/regular/hi.hpp>
#include <eve/module/core/regular/lohi.hpp>

namespace eve
{

  template<typename Options>
  struct lo_t : elementwise_callable<lo_t, Options>
  {
    template<typename T>
    struct result
    {
      using type = as_wide_as_t<downgrade_t<as_integer_t<element_type_t<T>,unsigned>>,T>;
    };

    template<eve::value T>
    constexpr EVE_FORCEINLINE typename result<T>::type
    operator()(T a) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((as<typename result<T>::type>{}), a);
    }

    EVE_CALLABLE_OBJECT(lo_t, lo_);
  };


//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var lo
//!   @brief Computes the least significant half of each lane.
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
//!      constexpr auto lo(value auto x)                           noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      * Computes the [elementwise](@ref glossary_elementwise)
//!        lower significant half of the  value bits,
//!        returning each element as an unsigned integer of half the size of the input element.
//!
//!    @note
//!      If you also need the lower part `hilo` is more efficient.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/lo.cpp}
//================================================================================================
  inline constexpr auto lo = functor<lo_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto lo_(EVE_REQUIRES(cpu_), O const&, T const& a0) noexcept
    {
      using elt_t = element_type_t<T>;
      if constexpr( sizeof(elt_t) == 1 ) // nibbles extraction
      {
        using ui_t = as_integer_t<T, unsigned>;
        auto uia0  = bit_cast(a0, as<ui_t>());
        return ui_t(uia0 & ui_t(0xF));
      }
      else
      {
        auto [l, _] = lohi(a0);
        return l;
      }
    }
  }
}
