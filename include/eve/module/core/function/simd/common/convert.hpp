//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CONVERT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CONVERT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>

namespace eve::detail
{
//   // Required by the aggregate skeleton - IF YOU END UP HERE, YOU'VE BEEN A NAUGHTY USER
//   template<typename T, typename U>
//   U convert_(EVE_SUPPORTS(cpu_),T const &,as_<U> const&);


  // Don't do anything if we idem-cast
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto convert_ ( EVE_SUPPORTS(cpu_),
                                    wide<T, N, ABI> const & v0, as_<T> const&
                                  ) noexcept
  {
    return v0;
  }

  // Generic case for arithmetic
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE wide<U,N> convert_( EVE_SUPPORTS(cpu_),
                                        wide<T, N, ABI> const & v0, as_<U> const& tgt
                                      ) noexcept
  {
    // Both source and target needs to be aggregate for the optimization to make sense
    if constexpr( is_aggregated_v<ABI> && is_aggregated_v<typename wide<U,N>::abi_type>)
    {
      return aggregate(eve::convert, v0, tgt);
    }
    else
    {
      // If not, just map static_cast
      return map( [](auto e, auto) { return static_cast<U>(e); }, v0, tgt );
    }
  }
  
  //////////////////////////////////////////////////////////////////////////////////////
  // pedantic case
  //////////////////////////////////////////////////////////////////////////////////////

  template<typename IN, typename N, typename ABI, typename OUT>
  EVE_FORCEINLINE wide<OUT,N> convert_( EVE_SUPPORTS(cpu_)
                                      , pedantic_type const & ped_
                                      ,  wide<IN, N, ABI> const & v0, as_<OUT> const& tgt
                                      ) noexcept
  {
    if constexpr(std::is_same_v<IN, double> && std::is_same_v<OUT, int64_t>)
    {
      const int32_t Vim32 = Valmin<int32_t>();
      const OUT Vim =  OUT(Vim32);
      const OUT Vax = -OUT(Vim32);
      auto z = v0*1.52587890625000e-05; //v0*2^(-16);
      auto t2 = trunc(z);
      auto t1 = z-t2; 
      auto z1 = convert(t1*65536.0, as<OUT>())+shl(convert(t2, as<OUT>()), 16);
      return if_else(logical_and(z1 == Vim, is_gtz(v0)), Vax, z1);
    }
    else if constexpr(std::is_floating_point_v<IN> && std::is_same_v<OUT, as_integer_t<IN, unsigned>> )
    {
      using r_t = as_integer_t<IN, unsigned>;
      using si_t = as_integer_t<IN, signed>;
      IN sign_f = inc(IN(Valmax<si_t>()));
      r_t sign_i = inc(r_t(Valmax<si_t>()));
      return if_else(is_less(v0, sign_f)
                    , bitwise_cast(convert(v0, as<OUT>()), as<wide<OUT, N>>())
                    , bitwise_cast(convert(v0 - sign_f, as<OUT>()), as<wide<OUT, N>>()) + sign_i
                    );
    }
    else
    {
      return convert(v0, as<OUT>()); 
    }
  }
  
  //////////////////////////////////////////////////////////////////////////////////////
  // saturated case
  //////////////////////////////////////////////////////////////////////////////////////
  
  template<typename IN, typename N, typename ABI, typename OUT>
  EVE_FORCEINLINE wide<OUT,N> convert_( EVE_SUPPORTS(cpu_)
                                      , saturated_type const & ped_
                                      , wide<IN, N, ABI> const & v0, as_<OUT> const& tgt
                                      ) noexcept
  {
    if constexpr(std::is_same_v<IN, OUT>)
    {
      return v0; 
    }
    else if constexpr(std::is_integral_v<OUT>)
    {
      if constexpr(std::is_floating_point_v<IN> || (sizeof(OUT) <= sizeof(IN)))
      {
        return convert(saturate(as<OUT>(), v0), tgt); 
      }
    }
    else        
    {
      return convert(v0, tgt);  
    } 
  }  
}

#endif
