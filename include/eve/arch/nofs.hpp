//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/wide.hpp>

namespace eve
{
  namespace detail {

#if defined(EVE_AVX512_DEFAULT_64_BYTES)
  constexpr bool avx512_default_64_bytes = true;
#else
  constexpr bool avx512_default_64_bytes = false;
#endif

  }  // namespace detail

  //================================================================================================
  //! @addtogroup arch
  //! @{
  //!   @var nofs_cardinal_v
  //!   @brief nofs stands for "no frequency scaling".
  //!
  //!   This refers to extreme frequency scaling one encounters when working with 64 byte
  //!   registers on intel. The processor scales frequency drammatically for a substantial
  //!   period of time. So even if the algorithm itself will run faster the overall perf
  //!   will go down. Generally speaking, 64 byte registers on intel make sense only
  //!   for really big data sets. `nofs_cardinal` will produce 32 byte registers on avx512.
  //!   If you would like to default to 64 byte registers, you can build with DEVE_AVX512_DEFAULT_64_BYTES.
  //!   This is probably a good idea on AMD-ZEN4 but we do not detect that at the moment.
  //!
  //!   @note: frquency scaling exists for avx2 as well but is generally considered
  //!   acceptable. For example popular implementations of libc use avx2, so you are very
  //!   likely already have it. You can always set the width manually if needed.
  //!
  //!   @note: `eve::algo` by default will use `nofs_cardinal`. See `allow_frequency_scaling`
  //!   trait.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi. defaults to current.
  //!
  //!    <br/>
  //!    #### Helpers
  //!
  //!    @code{.cpp}
  //!    template <scalar_value T, regular_abi ABI = eve::current_abi_type>
  //!    using nofs_cardinal_t = fixed<nofs_cardinal_v<T>>;
  //!
  //!    template <scalar_value T>
  //!    using nofs_wide = wide<T, nofs_cardinal_t<T>>;
  //!
  //!    template <plain_scalar_value T>
  //!    using nofs_logical = logical<nofs_wide<T>>;
  //!
  //!    @endcode
  //!
  //! @}
  //================================================================================================

  template <scalar_value T, regular_abi ABI = eve::current_abi_type>
  constexpr std::ptrdiff_t nofs_cardinal_v =
    (std::same_as<ABI, x86_512_> && !detail::avx512_default_64_bytes)
     ? expected_cardinal_v<T, x86_256_> : expected_cardinal_v<T, ABI>;

  template <scalar_value T, regular_abi ABI = eve::current_abi_type>
  using nofs_cardinal_t = fixed<nofs_cardinal_v<T>>;

  template <scalar_value T>
  using nofs_wide = wide<T, nofs_cardinal_t<T>>;

  template <plain_scalar_value T>
  using nofs_logical = logical<nofs_wide<T>>;

  template <typename T>
  using nofs_aligned_ptr = aligned_ptr<T, nofs_cardinal_t<T>>;
}
