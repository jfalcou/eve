//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/am.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <tuple>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U,  floating_real_value V>
  EVE_FORCEINLINE auto jacobi_elliptic_(EVE_SUPPORTS(cpu_)
                       , T u
                       , T x
                       , T tol = eps(as<T>())) noexcept
  {
    return arithmetic_call(jacobi_elliptic, u, x, tol);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE std::tuple < T, T, T>
  jacobi_elliptic_(EVE_SUPPORTS(cpu_)
                  , T u
                  , T x
                  , T tol = eps(as<T>())) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto phi = am(u, x, tol);
      auto [sn, cn] = sincos(phi);
      return {sn, cn, sqrt(oneminus(sqr(x*sn)))};
    }
    else
      return apply_over3(jacobi_elliptic, u, x, tol);
  }

  template<floating_real_value T, floating_real_value U,  decorator D>
  EVE_FORCEINLINE auto jacobi_elliptic_(EVE_SUPPORTS(cpu_)
                       , D const &
                       , T u
                       , U x
                       ) noexcept
  {
    return D()(jacobi_elliptic)(u, x, eps(as<element_type_t<T>>()));
  }

  template<floating_real_value T, floating_real_value U, floating_real_value V,  decorator D>
  EVE_FORCEINLINE  std::tuple < T, T, T>
  jacobi_elliptic_(EVE_SUPPORTS(cpu_)
                  , D const &
                  , T u
                  , U x
                  , V tol
                  ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
    auto phi = D()(am)(u, x, tol);
    auto [sn, cn] = sincos(phi);
    return {sn, cn, sqrt(oneminus(sqr(x*sn)))};
    }
    else
      return apply_over3(D()(jacobi_elliptic), u, x, tol);
  }

}
