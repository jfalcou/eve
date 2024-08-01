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
    template<scalar_value T>
    constexpr EVE_FORCEINLINE as_wide_t<T> operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    template<scalar_value T, std::ptrdiff_t N>
    constexpr EVE_FORCEINLINE as_wide_t<T, fixed<N>>
    operator()(T v, fixed<N> lanes) const noexcept { return EVE_DISPATCH_CALL(v, lanes); }

    // TODO: Remove this as it is a duplicata of broadcast_lane
    template<simd_value T, std::ptrdiff_t I>
    constexpr EVE_FORCEINLINE
    T operator()(T v, index_t<I> idx) const noexcept { return EVE_DISPATCH_CALL(v,idx); }

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
//!     template<eve::scalar_value T> eve::as_wide_t<T> broadcast(T v) noexcept;                            // 1
//!     template<eve::scalar_value T, std::ptrdiff_t N> as_wide_t<T> broadcast(T v, fixed<N> sz) noexcept;  // 2
//!     template<eve::simd_value T, std::size_t I> T broadcast(T v, index_t<I> i) noexcept;                 // 3
//!     template<eve::simd_value T, std::size_t I, std::ptrdiff_t N>
//!     eve::as_wide_t<T,fixed<N>> broadcast(T v, index_t<I> i, fixed<N> sz) noexcept;                      // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!     * `v`: A [value](@ref eve::simd_value).
//!     * `i`: An eve::index instance indicating which lane of `x` to broadcast.
//!     * `sz`: An eve::lane instance indicating how many lanes to broadcast to.
//!
//!   **Return value**
//!     1. A [SIMD value](@ref eve::simd_value) equals to `eve::as_wide_t<T>{v}`.
//!     2. A [SIMD value](@ref eve::simd_value) equals to `eve::as_wide_t<T,eve::fixed<N>>{v}`.
//!     3. A [SIMD value](@ref eve::simd_value) equals to `T{v.get(I)}`.
//!     4. A [SIMD value](@ref eve::simd_value) equals to `eve::as_wide_t<T,eve::fixed<N>>{v.get(I)}`.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/broadcast.cpp}
//================================================================================================
  inline constexpr auto broadcast = functor<broadcast_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/broadcast.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/broadcast.hpp>
#endif
