//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/memory.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/spy.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/replace.hpp>
#include <eve/module/core/regular/safe.hpp>
#include <eve/module/core/regular/unsafe.hpp>
#include <eve/module/core/regular/unalign.hpp>
#include <eve/traits/wide_value_type.hpp>
#include <eve/traits/as_translation.hpp>
#include <eve/concept/ptr_translation.hpp>
#include <eve/wide.hpp>

#include <iterator>

namespace eve::detail
{
  //================================================================================================
  // Load helper
  //================================================================================================
  template<typename Wide, typename Iterator>
  EVE_FORCEINLINE auto piecewise_load(Iterator ptr, as<Wide>) noexcept
  {
    auto impl = [&](auto... I)
    {
      std::array<element_type_t<Wide>, Wide::size()> values;

      values[0] = translate(*ptr);
      for(std::size_t i = 1; i < Wide::size(); ++i)
      {
        values[i] = translate(*(ptr = std::next(ptr)));
      }

      return Wide(values[I]...);
    };

    return apply<Wide::size()>(impl);
  }

  template<relative_conditional_expr C, typename Wide, typename Iterator>
  EVE_FORCEINLINE auto piecewise_load_cx(C const& cx, Iterator ptr, as<Wide> tgt) noexcept
  {
    if constexpr (C::is_complete)
    {
      if constexpr (C::is_inverted) return piecewise_load(ptr, tgt);
      else                          return detail::alternative(cx, Wide {}, tgt);
    }
    else
    {
      std::ptrdiff_t begin = cx.offset(tgt);
      std::ptrdiff_t end = begin + cx.count(tgt);

      Wide res = detail::alternative(cx, Wide { }, tgt);

      if (begin != end)
      {
        std::advance(ptr, begin);
        res.set(begin, *ptr);
        for (std::ptrdiff_t i = begin + 1; i < end; ++i)
        {
          ++ptr;
          res.set(i, translate(*ptr));
        }
      }

      return res;
    }
  }

  template<typename Wide, typename Pointer>
  EVE_FORCEINLINE auto aggregate_load(Pointer ptr, as<Wide>) noexcept
  {
    Wide that;

    auto cast = []<typename Ptr, typename Sub>(Ptr p, as<Sub>)
    {
      using type = value_type_t<Ptr>;
      using a_p = eve::aligned_ptr<const type, cardinal_t<Sub>>;
      if constexpr (std::is_pointer_v<Ptr>) return p;
      else                                  return a_p{p.get()};
    };

    that.storage().apply
    (
      [&]<typename... Sub>(Sub&... v)
      {
        int offset = 0;
        (((v = Sub(cast(ptr, as<Sub>{}) + offset), offset += Sub::size()), ...));
      }
    );

    return that;
  }

  //================================================================================================
  // Load impl
  //================================================================================================

  template<detail::data_source DS, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> load_impl(cpu_, DS src, as<logical<wide<T, N>>> tgt) noexcept
  {
    using w_src = wide_value_type_t<DS>;

    if constexpr (logical_simd_value<w_src> && abi_t<T, N>::is_wide_logical)
    {
      return bit_cast(load(ptr_cast<T const>(src), as<wide<T, N>>{}), tgt);
    }
    else
    {
      return to_logical(load(ptr_cast<T const>(src), as<wide<T, N>>{}));
    }
  }

  template<relative_conditional_expr C, detail::data_source DS, typename Wide>
  EVE_FORCEINLINE Wide load_cx_(C const& cx, DS src, as<Wide> tgt) noexcept
  {
    using e_t = typename pointer_traits<Wide>::value_type;
    using c_t = cardinal_t<Wide>;

    // If the ignore/keep is complete we can jump over if_else
    if constexpr (C::is_complete)
    {
      if constexpr (C::has_alternative) return Wide {cx.alternative};
      else                              return Wide {};
    }
    else if constexpr (instance_of<DS, aligned_ptr>)
    {
      constexpr bool is_aligned_enough = c_t() * sizeof(e_t) >= DS::alignment();

      if constexpr (!spy::supports::sanitizers_status && is_aligned_enough)
      {
        const auto res = eve::load[unsafe](src, tgt);

        if constexpr (C::has_alternative) return replace_ignored(res, cx, cx.alternative);
        else                              return res;
      }
      else
      {
        return eve::load[cx](src.get(), tgt);
      }
    }
    else if constexpr (logical_simd_value<Wide> && !Wide::abi_type::is_wide_logical)
    {
      using W = as_arithmetic_t<Wide>;
      using T = element_type_t<W>;

      auto const mcx = map_alternative(cx, [](auto alt) { return alt.mask(); });
      return to_logical(load[mcx](ptr_cast<T const>(src), as<W>{}));
    }
    else
    {
      auto offset = cx.offset(tgt);

      if constexpr (C::has_alternative)
      {
        [[maybe_unused]] Wide that(cx.alternative);
        auto                *dst = (e_t *)(&that.storage());
        std::memcpy((void *)(dst + offset), src + offset, sizeof(e_t) * cx.count(tgt));
        return that;
      }
      else
      {
        [[maybe_unused]] Wide that = {};
        auto                *dst = (e_t *)(&that.storage());
        std::memcpy((void *)(dst + offset), src + offset, sizeof(e_t) * cx.count(tgt));
        return that;
      }
    }
  }

  template<callable_options O, std::input_iterator It, typename Wide>
  EVE_FORCEINLINE Wide load_iterator_(O const& opts, It src, as<Wide> tgt) noexcept
  {
    if constexpr (std::contiguous_iterator<It>)
    {
      return load.behavior(cpu_{}, opts, std::to_address(src), tgt);
    }
    else if constexpr (logical_simd_value<Wide> && !Wide::abi_type::is_wide_logical)
    {
      return to_logical(piecewise_load_cx(opts[condition_key], src, as<as_arithmetic_t<Wide>>{}));
    }
    else
    {
      return piecewise_load_cx(opts[condition_key], src, tgt);
    }
  }

  template<relative_conditional_expr C, detail::data_source DS, typename Wide>
  EVE_FORCEINLINE Wide load_common(auto api, C const& cx, DS src, as<Wide> tgt) noexcept
  {
    constexpr auto aggregated = has_aggregated_abi_v<Wide>;
    constexpr auto emulated = has_emulated_abi_v<Wide>;

    if constexpr (aggregated || emulated)
    {
      if constexpr (std::same_as<C, ignore_none_>)
      {
        if constexpr (logical_simd_value<Wide>)
        {
          return load_impl(cpu_{}, src, tgt);
        }
        else if constexpr (aggregated)
        {
          return aggregate_load(src, tgt);
        }
        else if constexpr (emulated)
        {
          return piecewise_load(unalign(src), tgt);
        }
      }
      else
      {
        return load_cx_(cx, src, tgt);
      }
    }
    else if constexpr (requires { load_impl(api, cx, src, tgt); })
    {
      // If there's a backend that can handle the load along with the condition,
      // we use it directly.
      return load_impl(api, cx, src, tgt);
    }
    else if constexpr (std::same_as<C, ignore_none_>)
    {
      return load_impl(api, src, tgt);
    }
    else
    {
      return load_cx_(cx, src, tgt);
    }
  }

  template<callable_options O, detail::data_source DS, typename Wide>
  SPY_DISABLE_SANITIZERS Wide load_unsafe_(O const& opts, DS src, as<Wide> tgt) noexcept
  {
    if constexpr (spy::supports::sanitizers_status)
    {
      auto cx = opts[condition_key];

      auto res = detail::alternative(cx, Wide {}, tgt);

      auto offset = cx.offset(tgt);
      auto count  = cx.count(tgt);

      for (std::ptrdiff_t i = offset; i != count + offset; ++i)
        res.set(i, src[i]);

      return res;
    }
    else
    {
      return eve::load[opts.drop(unsafe2)](src, tgt);
    }
  }

  template<callable_options O, detail::data_source DS, typename Wide>
  EVE_FORCEINLINE Wide load_(EVE_REQUIRES(cpu_), O const& opts, DS src, as<Wide> tgt) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    [[maybe_unused]] auto cx = opts[condition_key];

    if constexpr (translatable_ptr<DS>)
    {
      return load.behavior(cpu_{}, opts, translate_ptr(src), tgt);
    }
    else if constexpr (requires { src.load(opts, tgt); })
    {
      return src.load(opts, tgt);
    }
    else if constexpr (std::input_iterator<DS> && !detail::scalar_pointer<DS>)
    {
      return load_iterator_(opts, src, tgt);
    }
    else if constexpr (O::contains(unsafe2))
    {
      return load_unsafe_(opts, src, tgt);
    }
    else if constexpr (has_bundle_abi_v<Wide>)
    {
      Wide res;

      if constexpr (C::has_alternative)
      {
        kumi::for_each( [=]<typename M>(M& m, auto part_alt, auto p) {
              auto new_c = cx.map_alternative([&](auto) { return part_alt; });
              m = load[opts][new_c](p, as<M>{});
            }
            , res.storage(), cx.alternative, src
            );
      }
      else
      {
        kumi::for_each( [=]<typename M>(M& m, auto p) { m = load[opts](p, as<M>{}); }
                      , res.storage(), src
                      );
      }

      return res;
    }
    else
    {
      return load_common(current_api, opts[condition_key], src, tgt);
    }
  }
}
