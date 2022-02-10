//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/all.hpp>
#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/module/core/regular/combine.hpp>
#include <eve/product_type.hpp>
#include <eve/traits/as_wide.hpp>

namespace eve::detail
{
  struct convert_lambda
  {
    template<typename T, typename M>
    EVE_FORCEINLINE constexpr void operator()(T const& in, M* res_m) const noexcept
    {
      *res_m = eve::convert(in, eve::as<element_type_t<M>>{});
    }
  };

  template<product_type T, product_type U>
  requires(kumi::result::flatten_all_t<T>::size() == kumi::result::flatten_all_t<U>::size())
  EVE_FORCEINLINE auto convert_(EVE_SUPPORTS(cpu_), T const& v0, eve::as<U>)
  {
    if constexpr(std::same_as<element_type_t<T>, U>)
    {
      return v0;
    }
    else
    {
      using out_t = std::conditional_t<scalar_value<T>, U, as_wide_t<U, cardinal_t<T>>>;
      out_t res;

      auto outs = kumi::flatten_all(res, [](auto& m) { return &m; });
      auto ins  = kumi::flatten_all(v0);

      kumi::for_each( convert_lambda{}, ins, outs );

      return res;
    }
  }

  template<value T, scalar_value U>
  requires( !product_type<T> && !product_type<U>)
  EVE_FORCEINLINE auto convert_(EVE_SUPPORTS(cpu_), T const &v0, as<U> const &tgt) noexcept
  {
    if constexpr(std::same_as<element_type_t<T>, U>)
    {
      return v0;
    }
    else
    {
      if constexpr( scalar_value<T> )
      {
        return static_cast<U>(v0);
      }
      else
      {
        using out_t = as_wide_t<U, cardinal_t<T>>;

        // If input or output are aggregated, we can slice and combine without lose of performance
        if constexpr( has_aggregated_abi_v<T> || has_aggregated_abi_v<out_t> )
        {
          auto[l,h] = v0.slice();
          auto ll = eve::convert(l,tgt);
          auto hh = eve::convert(h,tgt);
          return out_t{ll,hh};
        }
        else
        {
          return map(convert, v0, tgt);
        }
      }
    }
  }

  template<value T, scalar_value U>
  EVE_FORCEINLINE auto convert_ ( EVE_SUPPORTS(cpu_)
                                , logical<T> const &v0
                                , [[maybe_unused]] as<logical<U>> const & tgt
                                ) noexcept
  {
    if constexpr(std::same_as<element_type_t<T>, U>)
    {
      return v0;
    }
    else
    {
      if constexpr( scalar_value<T> )
      {
        return static_cast<logical<U>>(v0.bits());
      }
      else
      {
        using abi_t = typename T::abi_type;
        using out_t = as_wide_t<logical<U>, cardinal_t<logical<T>>>;

        // If input or output are aggregated, we can slice and combine without lose of performance
        if constexpr( !abi_t::is_wide_logical)
        {
          // If input or output are aggregated, we can slice and combine without lose of performance
          if constexpr( has_aggregated_abi_v<T> || has_aggregated_abi_v<out_t> )
          {
            auto[l,h] = v0.slice();
            auto ll = eve::convert(l,tgt);
            auto hh = eve::convert(h,tgt);
            return out_t{ll,hh};
          }
          else
          {
            using s_t = typename out_t::storage_type;
            using i_t = typename s_t::type;
            return out_t( s_t{ static_cast<i_t>(v0.storage().value) } );
          }
        }
        else
        {
          using s_in_t  = std::make_signed_t<typename logical<T>::bits_type::value_type>;
          using v_int_t = typename logical<T>::bits_type::template rebind<s_in_t, cardinal_t<out_t>>;
          using s_out_t = std::make_signed_t<typename logical<U>::bits_type>;

          // Just convert the bit and bitcast back to the proper output
          return bit_cast ( convert ( bit_cast(v0.bits(),as<v_int_t>{})
                                    , as<s_out_t>{}
                                    )
                          , as<out_t>{}
                          );
        }
      }
    }
  }
}
