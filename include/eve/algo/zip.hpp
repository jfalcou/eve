//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/as_range.hpp>
#include <eve/algo/range_ref.hpp>
#include <eve/algo/concepts/relaxed.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/zip_iterator.hpp>

#include <eve/algo/concepts/detail.hpp>

#include <eve/algo/detail/preprocess_zip_range.hpp>

#include <eve/detail/kumi.hpp>

namespace eve::algo
{
  template <relaxed_range ...Rngs>
  struct zip_range;

  template <typename TraitsSupport>
  // this is zip traits, not algo traits.
  struct zip_ : TraitsSupport
  {
   private:
     template <typename ...Components>
     EVE_FORCEINLINE std::ptrdiff_t compute_distance(Components&& ... components) const
     {
       std::ptrdiff_t res = -1;
       auto process_one = [&]<typename C>(C const& c) mutable {
         if constexpr (relaxed_range<C>)
         {
           std::ptrdiff_t cur = c.end() - c.begin();
           if (res == -1) res = cur;
           // We'd need to support zipping to min size at some point
           EVE_ASSERT(res == cur, "Can't zip ranges of different sizes");
         }
       };
       (process_one(components), ...);
       return res;
     }

     template <typename ...Components>
     EVE_FORCEINLINE auto perform_replacements(std::ptrdiff_t distance, Components&& ... components) const
     {
       return kumi::tuple{
         [&]<typename C>(C&& c)
         {
           if constexpr (relaxed_range<C>) return range_ref(std::forward<C>(c));
           else                            return as_range(c, unalign(c) + distance);
         }(components)...
       };
     }

    template <typename ...Components>
    EVE_FORCEINLINE auto type_to_convert_to(Components&&...) const
    {
      using traits_type = typename TraitsSupport::traits_type;

      if constexpr( traits_type::contains(force_type_key) )
      {
        return rbr::get_type_t<traits_type, force_type_key> {};
      }
      else
      {
        using common_zip = eve::common_type<value_type_t<std::remove_cvref_t<Components>>...>;

        using Param = rbr::get_type_t<traits_type, common_with_types_key>;

        return []<typename... ParamTypes, typename... ZipTypes>(eve::common_type<ParamTypes...>,
                                                                eve::common_type<ZipTypes...>)
        {
          return eve::common_type<ParamTypes..., ZipTypes...> {};
        }
        (Param {}, common_zip {});
      }
    }

   public:

    template <typename ...Components>
      requires ((relaxed_range<Components> || relaxed_iterator<Components>) && ...)
    EVE_FORCEINLINE auto operator()(Components&& ... components) const;
  };

  inline constexpr auto zip = function_with_traits<zip_>;

  template <typename TraitsSupport>
  template<typename... Components>
    requires((relaxed_range<Components> || relaxed_iterator<Components>)&&...)
  EVE_FORCEINLINE auto zip_<TraitsSupport>::operator()(Components &&...components) const
  {
    using traits_type = typename TraitsSupport::traits_type;

    static_assert(traits_type::contains_only(force_type_key, common_with_types_key));

    if constexpr (has_type_overrides_v<traits_type>)
    {
      auto to = type_to_convert_to(std::forward<Components>(components)...);
      using T = typename decltype(to)::type;
      return zip(algo::convert(std::forward<Components>(components), eve::as<T>{})...);
    }
    else if constexpr( (relaxed_iterator<Components> && ...) )
    {
      return zip_iterator {components...};
    }
    else
    {
      std::ptrdiff_t distance = compute_distance(components...);
      return zip_range { perform_replacements(distance, components...) };
    }
  }

  template <relaxed_range ...Rngs>
  struct zip_range : kumi::tuple<Rngs...>
  {
    using is_non_owning = void;

    EVE_FORCEINLINE zip_range(kumi::tuple<Rngs...> ranges):
      kumi::tuple<Rngs...>(ranges)
    {
    }

    // Traits support
    template<typename Settings>
    EVE_FORCEINLINE auto operator[](traits<Settings> tr) const
    {
      return kumi::apply(zip[tr], *this);
    }

    template <rbr::concepts::option Trait>
    EVE_FORCEINLINE auto operator[](Trait one_tr) const
    {
      return operator[](eve::algo::traits(one_tr));
    }

    EVE_FORCEINLINE auto begin() const
    {
      return kumi::apply(zip, kumi::map([](auto r) { return r.begin(); }, *this));
    }

    EVE_FORCEINLINE auto end() const
    {
      return kumi::apply(zip, kumi::map([](auto r) { return r.end(); }, *this));
    }

    template <typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr, zip_range self)
    {
      return detail::preprocess_zip_range(tr, self);
    }

    template <typename T>
    EVE_FORCEINLINE friend auto tagged_dispatch(convert_, zip_range self, eve::as<T> tgt)
    {
      return detail::convert_zipped(self, tgt);
    }
  };
}

namespace std
{
  template <typename ...Ranges>
  struct tuple_size<eve::algo::zip_range<Ranges...>> :
    std::tuple_size<kumi::tuple<Ranges...>>
  {
  };

  template <std::size_t I, typename ...Ranges>
  struct tuple_element<I, eve::algo::zip_range<Ranges...>> :
    std::tuple_element<I, kumi::tuple<Ranges...>>
  {
  };
}

namespace eve::algo::detail
{
  template<typename T>
  struct print_type;

  template<std::size_t, std::size_t>
  struct print_size;

  template<typename Self, typename T>
  EVE_FORCEINLINE auto convert_zipped(Self self, eve::as<T> tgt)
  {
    if constexpr( std::same_as<value_type_t<Self>, T> ) return self;
    else
    {
      // FIX-918: reconstruct the original components.
      //          support converting components inside zip.
      auto make_as = []<typename M>(M) { return as<M> {}; };
      using t_flat = kumi::result::map_t<decltype(make_as), kumi::result::flatten_all_t<T>>;

      auto self_flat = kumi::flatten_all(self);

      auto flat_cvt = kumi::apply(zip, kumi::map(convert, self_flat, t_flat {}));
      return convert.no_tagged_dispatch(flat_cvt, tgt);
    }
  }
}
