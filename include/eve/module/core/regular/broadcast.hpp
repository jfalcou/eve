//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once


#include <eve/arch.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/same_lanes.hpp>

namespace eve
{
  template<typename Options>
  struct broadcast_t : callable<broadcast_t, Options>
  {
    template<simd_value T, std::ptrdiff_t I>
    constexpr EVE_FORCEINLINE T
    operator()(T v, index_t<I> idx) const noexcept { return EVE_DISPATCH_CALL(v, idx); }

    template<simd_value T, std::ptrdiff_t I, std::ptrdiff_t N>
    constexpr EVE_FORCEINLINE as_wide_t<T, fixed<N>>
    operator()(T v, index_t<I> idx, fixed<N> lanes) const noexcept { return EVE_DISPATCH_CALL(v, idx, lanes); }

    EVE_CALLABLE_OBJECT(broadcast_t, broadcast_);
  };

  //================================================================================================
  //! @addtogroup core_simd
  //! @{
  //!   @var broadcast
  //!   @brief Computes the
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
  //!      template< eve::value T >
  //!      T broadcast(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `x`:  An instance of an [SIMD value](@ref eve::simd_value)
  //!
  //!      * `i`:  An eve::index indicating which lane of `x` to broadcast
  //!
  //!    **Return value**
  //!
  //!      *  If `x` is an instance of an [SIMD value](@ref eve::simd_value) `T`, the call is
  //!      equivalent to `T{x.get(I)}`.
  //!      *  If `x` is an instance of a [scalar value](@ref eve::scalar_value) the call simply
  //!      returns `x`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/broadcast.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto broadcast = functor<broadcast_t>;
}

#include <eve/module/core/regular/impl/broadcast.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/broadcast.hpp>
#endif
