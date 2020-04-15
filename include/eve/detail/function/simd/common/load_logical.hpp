//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_LOAD_LOGICAL_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_LOAD_LOGICAL_HPP_INCLUDED

#include <eve/as.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::detail
{
  //================================================================================================
  // Common logical case
  //================================================================================================
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto load(as_<logical<wide<T, N, ABI>>> const &,
                            ABI const & mode,
                            logical<T> const*ptr) noexcept requires native<ABI>
  {
    using type = typename logical<wide<T, N, ABI>>::storage_type;
    return type(load(as_<wide<T, N, ABI>> {}, mode, (T *)ptr));
  }

  template<typename T, typename N, std::size_t Align, typename ABI>
  EVE_FORCEINLINE auto
  load(as_<logical<wide<T, N, ABI>>> const &tgt,
       ABI const &                          mode,
       aligned_ptr<logical<T> const, Align> ptr) noexcept requires native<ABI>
  {
    using type = typename logical<wide<T, N, ABI>>::storage_type;
    return type(load(as_<wide<T, N, ABI>>{}, mode, aligned_ptr<T, Align>((T *)ptr.get())));
  }

  template<typename T, typename N, std::size_t Align, typename ABI>
  EVE_FORCEINLINE auto
  load(as_<logical<wide<T, N, ABI>>> const &tgt,
       ABI const &                          mode,
       aligned_ptr<logical<T>, Align>       ptr) noexcept requires native<ABI>
  {
    using type = typename logical<wide<T, N, ABI>>::storage_type;
    return type(load(as_<wide<T, N, ABI>> {}, mode, aligned_ptr<T, Align>((T *)ptr.get())));
  }
}

#endif
