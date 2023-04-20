//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/fft/utils/aos_soa.hpp>
#include <type_traits>
#include <vector>
#include <iostream>

namespace eve::detail
{
  template<decorator D, typename F, range R, scalar_value T>
  EVE_FORCEINLINE void ifft_(EVE_SUPPORTS(cpu_)
                            , D const &
                            , F const & fft
                            , R & f
                            , T const & fac) noexcept
  requires(eve::is_complex_v<typename R::value_type> && is_one_of<D>(types<aos_type, soa_type> {}))
  {
    auto pr = [](auto name, auto v){
         std::cout << name << " = (";
         for(size_t i=0; i < std::size(v); ++i) std::cout << v.get(i) << " ";
      std::cout << ")\n";
    };
     auto conjmuli = []<typename C>(C x){
      auto  [r, i] = x; return C(i, r);
    };
    if constexpr(std::same_as<D, aos_type>)
      std::transform(f.data(), f.data()+f.size(), f.data(), conjmuli);
    else  if constexpr(std::same_as<D, soa_type>)
    {
      pr("f avant ", f);
      eve::algo::transform_inplace(f, conjmuli);
      pr("f apres ",  f);
    }
    std::cout << "fac " << fac << std::endl;
    fft(f, fac);
    if constexpr(std::same_as<D, aos_type>)
      std::transform(f.data(), f.data()+f.size(), f.data(), conjmuli);
    else  if constexpr(std::same_as<D, soa_type>)
      eve::algo::transform_inplace(f, conjmuli);
  }

  /////////////////////////////////////////////////////////
  // default is soa
  template<typename F, range R, scalar_value T>
  EVE_FORCEINLINE void ifft_(EVE_SUPPORTS(cpu_)
                            , F const & fft
                            , R & f
                            , T const & fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    return soa(ifft)(fft, f, fac);
  }

  template<typename F, range R, scalar_value T>
  EVE_FORCEINLINE void ifft_(EVE_SUPPORTS(cpu_)
                            , F const & fft
                            , R & fr
                            , R & fi
                            , T const & fac) noexcept
  requires(std::is_floating_point_v<typename R::value_type>)
  {
    fft(fi, fr, fac);
    std::swap(fr, fi);
  }


}
