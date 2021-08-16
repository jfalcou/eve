//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/pattern.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup shuffling
  //! @{
  //! @var broadcast
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/broadcast.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing a broadcast shuffling.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the absolute value of its parameter               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<std::size_t I>
  //!  auto operator()(eve::simd_value auto const& x, eve::index_t<I> i ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `x`:  An instance of an \ref simd_value
  //!
  //! `i`:  An eve::index indicating which lane of `x` to broadcast
  //!
  //! **Return value**
  //!
  //! If `x` is an instance of an [SIMD value](@ref simd_value) `T`, the call is equivalent to `T{x.get(I)}`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/n5Tx7bGKW)
  //!
  //! @include{lineno} doc/core/broadcast.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(broadcast_, broadcast);

  namespace detail
  {
    //==============================================================================================
    // Detects <N,...,N> as a broadcast
    template<int I0, int... I> inline constexpr bool is_broadcast = ((I0 != na_) && ... && (I0==I));
  }
}

#include <eve/detail/function/simd/common/broadcast.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/broadcast.hpp>
#endif
