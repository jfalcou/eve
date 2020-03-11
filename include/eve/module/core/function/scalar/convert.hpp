//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_CONVERT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_CONVERT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/max.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/clamp.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

namespace eve::detail
{
  // Don't do anything if we idem-cast
  template<typename IN>
  EVE_FORCEINLINE auto convert_ ( EVE_SUPPORTS(cpu_),
                                    IN const & v0, as_<IN> const&
                                  ) noexcept
  requires(IN, vectorizable<IN>)
  {
    return v0;
  }

  template<typename IN, typename OUT>
  EVE_FORCEINLINE auto convert_( EVE_SUPPORTS(cpu_),
                                 IN const & v0, as_<OUT> const& tgt
                               ) noexcept
  requires(OUT, vectorizable<IN>, vectorizable<OUT>)
  {
    return static_cast<OUT>(v0);
  }
    
  //////////////////////////////////////////////////////////////////////////////////////
  // saturated case
  //////////////////////////////////////////////////////////////////////////////////////
  template<typename IN, typename OUT>
  EVE_FORCEINLINE auto convert_( EVE_SUPPORTS(cpu_)
                                 , saturated_type const &
                                 , IN const & v0, as_<OUT> const& tgt
                                 ) noexcept
  requires(OUT, vectorizable<IN>, vectorizable<OUT>)
  {
    return convert(saturate(v0, tgt), tgt); 
  }
}

#endif
