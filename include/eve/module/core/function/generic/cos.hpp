//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_COS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_COS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <eve/module/core/detail/scalar/rempio2_kernel.hpp>
#include <eve/module/core/detail/simd/rempio2_kernel.hpp>
#include <eve/module/core/detail/generic/trig_finalize.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/rempio2.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T a0) noexcept
  {
    if constexpr(native<T>)
    {
      auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); //0.61685027506808491367715568749226 but rounded upward
      auto x2 = sqr(a0);
      auto x2nlepi2_16 = is_not_less_equal(x2, pi2_16);
      if constexpr(scalar_value<T>)
        return (x2nlepi2_16) ? Nan<T>() : cos_eval(x2);
      else
        return if_else(x2nlepi2_16, eve::allbits_, cos_eval(x2));
    }
    else return apply_over(restricted_(cos), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                      , small_type const &
                                      , T a0) noexcept
  {
    if constexpr(native<T>)
    {
      T x = eve::abs(a0);
      auto xnlepio2 = is_not_less_equal(x, Pio_2<T>());
      if constexpr(scalar_value<T>) if (xnlepio2) return Nan<T>();
      auto reduce = [](auto x){
          auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
          auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
          auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
          auto xr = x-pio2_1;
          xr -= pio2_2;
          xr -= pio2_3;
          return xr;
      };
      if constexpr(scalar_value<T>)
      {
        using i_t =  as_integer_t<T, signed>;
        i_t n = x > Pio_4<T>();
        if (n)
        {
          auto xr =  reduce(x);
          return bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T)*8-1));
        }
        else return cos_eval(sqr(x));
      }
      else
      {
        using elt_t = element_type_t<T>;
        auto n = binarize(is_not_less_equal(x, Pio_4(as(x))));
        auto sign_bit = binarize(is_nez(n), Signmask<elt_t>());
        auto xr =  reduce(x);
        xr = if_else(n, xr, x);
        auto z = sqr(xr);
        auto se = bit_xor(sin_eval(z, xr), sign_bit);
        auto ce = cos_eval(z);
        auto z1 = if_else(n, se, ce);
        return if_else(xnlepio2, eve::allbits_, z1);
      }
    }
    else return apply_over(small_(cos), a0);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big
  template<typename D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                     , D  const &
                                     , T a0) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(scalar_value<T>) if (is_not_finite(a0)) return Nan<T>();
      auto x =  abs(a0);
      auto [fn, xr, dxr] = D()(rempio2)(x);
      return cos_finalize(fn, xr, dxr);
    }
    else return apply_over(D()(cos), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  {
    auto x =  abs(a0);
         if (all(x <= Pio_4(as(x))))                     return restricted_(cos)(a0);
    else if(all(x <= Pio_2(as(x))))                      return small_(cos)(a0);
    else if(all(x <= Rempio2_limit(medium_type(), T()))) return medium_(cos)(a0);
    else                                                 return big_(cos)(a0);
  }

}

#endif
