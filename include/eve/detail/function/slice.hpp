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

namespace eve
{
  template<std::size_t Slice>
  struct  slice_t
        : std::integral_constant<std::size_t, Slice>
  {};

  using upper_slice_t = slice_t<1>;
  using lower_slice_t = slice_t<0>;

  //================================================================================================
  //! @addtogroup simd
  //! @{
  //================================================================================================
  //! @brief Tag to select the upper slice of a simd_value
  inline constexpr upper_slice_t const upper_ = {};

  //! @brief Tag to select the lower slice of a simd_value
  inline constexpr lower_slice_t const lower_ = {};
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<typename Options>
    struct slice_callable_t : callable<slice_callable_t, Options>
    {
      template<typename W>
      EVE_FORCEINLINE constexpr auto operator()(W v) const noexcept
      {
        return EVE_DISPATCH_CALL(v);
      }

      template<typename W, std::size_t Slice>
      EVE_FORCEINLINE constexpr auto operator()(W v, slice_t<Slice> s) const noexcept
      {
        return EVE_DISPATCH_CALL(v, s);
      }

      EVE_CALLABLE_OBJECT(slice_callable_t, slice_);
    };

    inline constexpr auto slice = functor<detail::slice_callable_t>;
  }
}

#include <eve/detail/function/simd/common/slice.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/slice.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/slice.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/slice.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/slice.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/detail/function/simd/riscv/slice.hpp>
#endif
