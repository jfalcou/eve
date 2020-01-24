//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_BIT_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_BIT_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/function/simd/detail/bit_cast.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename U, typename M>
  EVE_FORCEINLINE wide<U, M, ppc_> bit_cast_(EVE_SUPPORTS(vmx_),
                                                 wide<T, N, ppc_> const &v0,
                                                 as_<wide<U, M, ppc_>> const &) noexcept
  {
    using type = wide<U, M, ppc_>;
    return type((typename type::storage_type)(v0.storage()));
  }

  // PPC supports logical bit casting
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(vmx_),
                                     wide<Source, N, ppc_> const &              v0,
                                     as_<logical<wide<Target, M, ppc_>>> const &tgt) noexcept
  {
    return a2l_cast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(vmx_),
                                     logical<wide<Source, N, ppc_>> const &v0,
                                     as_<wide<Target, M, ppc_>> const &    tgt) noexcept
  {
    return l2a_cast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(vmx_),
                                     logical<wide<Source, N, ppc_>> const &     v0,
                                     as_<logical<wide<Target, M, ppc_>>> const &tgt) noexcept
  {
    return l2l_cast_(v0, tgt);
  }
}

#endif
