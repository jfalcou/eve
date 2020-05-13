//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_CONVERT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_CONVERT_HPP_INCLUDED

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/trunc.hpp>

namespace eve::detail
{
  // Don't do anything if we idem-cast
  template<value IN>
  EVE_FORCEINLINE auto
  convert_(EVE_SUPPORTS(cpu_), IN const &v0, as_<element_type_t<IN>> const &) noexcept
  {
    return v0;
  }

  template<value IN, scalar_value OUT>
  EVE_FORCEINLINE auto convert_(EVE_SUPPORTS(cpu_), IN const &v0, as_<OUT> const &tgt) noexcept
  {
    if constexpr( scalar_value<IN> )
      return static_cast<OUT>(v0);
    else
      return map(convert, v0, tgt);
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // saturated case
  //////////////////////////////////////////////////////////////////////////////////////
  template<value IN, scalar_value OUT>
  EVE_FORCEINLINE auto
  convert_(EVE_SUPPORTS(cpu_), saturated_type const &, IN const &v0, as_<OUT> const &tgt) noexcept
  {
    return convert(saturate(v0, tgt), tgt);
  }

  //================================================================================================
  // pedantic case
  //================================================================================================
  template<value IN, scalar_value OUT>
  EVE_FORCEINLINE auto convert_(EVE_SUPPORTS(cpu_),
                                pedantic_type const &ped_,
                                IN const &           v00,
                                as_<OUT> const &     tgt) noexcept
  {
    using elt_tin = element_type_t<IN>;
    if constexpr( has_aggregated_abi_v<IN> )
    {
      return aggregate(eve::pedantic_(eve::convert), v00, tgt);
    }
    else if constexpr( std::is_same_v<elt_tin, double> && std::is_same_v<OUT, int64_t> )
    {
      const int32_t Vim32 = Valmin<int32_t>();
      const OUT     Vim   = OUT(Vim32);
      const OUT     Vax   = -OUT(Vim32);
      auto          z     = v00 * 1.52587890625000e-05; // v0*2^(-16);
      auto          t2    = trunc(z);
      auto          t1    = z - t2;
      auto          z1    = convert(t1 * 65536.0, as<OUT>()) + shl(convert(t2, as<OUT>()), 16);
      return if_else(logical_and(z1 == Vim, is_gtz(v00)), Vax, z1);
    }
    else if constexpr( floating_real_value<
                           IN> && std::is_same_v<OUT, as_integer_t<elt_tin, unsigned>> )
    {
      auto v0    = eve::max(v00, Zero(as(v00)));
      using r_t  = as_integer_t<IN, unsigned>;
      using si_t = as_integer_t<IN, signed>;
      IN  sign_f = inc(IN(Valmax<si_t>()));
      r_t sign_i = inc(r_t(Valmax<si_t>()));
      return if_else(is_less(v0, sign_f),
                     bit_cast(convert(v0, as<OUT>()), as<OUT>()),
                     bit_cast(convert(v0 - sign_f, as<OUT>()), as<OUT>()) + sign_i);
    }
    else if constexpr( signed_value<IN> && unsigned_value<OUT> )
    {
      return convert(eve::max(v00, Zero(as(v00))), as<OUT>());
    }
    else
    {
      return convert(v00, as<OUT>());
    }
  }

}

#endif
