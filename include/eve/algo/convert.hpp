//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/detail/convert.hpp>

#include <eve/algo/detail/preprocess_range.hpp>
#include <eve/algo/concepts/value_type.hpp>
#include <eve/algo/range_ref.hpp>

namespace eve::algo
{
  template <typename I, typename T>
  struct converting_iterator;

  template <non_owning_range R, typename T>
  struct converting_range;

  template <typename Wrapped, typename T>
  EVE_FORCEINLINE auto convert_::operator()(Wrapped&& wrapped, eve::as<T> tgt) const
  {
    using no_ref = std::remove_reference_t<Wrapped>;
    using no_cvref = std::remove_cvref_t<Wrapped>;

         if constexpr ( relaxed_range<no_ref> && !non_owning_range<no_cvref> ) return take_range_ref(std::forward<Wrapped>(wrapped));
    else if constexpr ( std::same_as<value_type_t<no_cvref>, T>              ) return wrapped;
    else if constexpr ( detail::instance_of<no_cvref, converting_range>      ) return operator()(wrapped.base, tgt);
    else if constexpr ( detail::instance_of<no_cvref, converting_iterator>   ) return operator()(wrapped.base, tgt);
    else if constexpr ( non_owning_range<no_cvref>                           ) return converting_range<no_cvref, T>{wrapped};
    else                                                                       return converting_iterator<no_cvref, T>{wrapped};
  }

/*
  template <non_owning_range R, typename T>
  struct converting_range
  {
    R base;

    EVE_FORCEINLINE explicit converting_range(R r) : base(r) {}

    EVE_FORCEINLINE auto begin() const
    {
      return convert(base.begin(), eve::as<T>{});
    }

    EVE_FORCEINLINE auto end() const
    {
      return convert(base.end(), eve::as<T>{});
    }

    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, auto tr, converting_range self)
    {
      auto tr_internal = tr.default_to(eve::algo::traits(force_type<T>));
      auto processed = preprocess_range(traits_internal, self.base);
      // drop from processed traits force_type. FIX-906
      return detail::preprocess_range_result(
        eve::algo::traits{},
        processed.begin(),
        processed.end(),
        [processed](auto i) { return processed.to_output(i);  }
      );
    }
  };
  */
}

#include <eve/algo/converting_iterator.hpp>
