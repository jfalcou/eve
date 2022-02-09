//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/relaxed.hpp>
#include <eve/algo/concepts/nothing.hpp>
#include <eve/algo/concepts/types_to_consider.hpp>
#include <eve/algo/iterator_helpers.hpp>
#include <eve/conditional.hpp>
#include <eve/traits/as_wide.hpp>

#include <eve/function/unalign.hpp>

namespace eve::algo::views
{
  namespace detail
  {
    template <typename LoadOp, typename Base>
    using map_value_type_t = decltype(std::declval<LoadOp>()(std::declval<value_type_t<Base>>()));

    template <typename LoadOp, typename Base>
    using map_types_to_consider = kumi::result::cat_t<kumi::tuple<map_value_type_t<LoadOp, Base>>,
                                                     types_to_consider_for_t<Base>>;

    template <typename Base, typename StoreOp>
    struct bound_store_op
    {
      StoreOp store_op;

      EVE_FORCEINLINE auto operator()(auto v) const
      {
        return store_op(v, as<value_type_t<Base>>{});
      }
    };

    template <typename Base, typename StoreOp>
    auto bind_store_op(StoreOp store_op)
    {
      return bound_store_op<Base, StoreOp>{store_op};
    }
  }

  //================================================================================================
  //! @addtogroup algo_concepts
  //! @{
  //!  @struct map_load_op
  //!  @brief requirement for the operation applied on read/load in map.
  //!         should work on both scalar and wide for the underlying iterator
  //!         for any cardinal.
  //!
  //!   **Required header:** #include <eve/algo/views/map.hpp>
  //!
  //!   Has a shorthand `eve::views::map_load_op` in `<eve/views/map.hpp>`
  //!
  //! @}
  //================================================================================================

  template <typename Op, typename Base>
  concept map_load_op = std::copyable<Op>
    && std::regular_invocable<Op, value_type_t<Base>>
    && std::regular_invocable<Op, as_wide_t<value_type_t<Base>>>;

  //================================================================================================
  //! @addtogroup algo_concepts
  //! @{
  //!  @struct map_store_op
  //!  @brief requirement for the operation applied on store in map.
  //!         should work on both scalar and wide for the underlying iterator
  //!         for any cardinal.
  //!
  //!         accepts the `as<value_type_t<Base>>` for convinience
  //!         (so that it can be defined without knowing the underlying type).
  //!
  //!   **Required header:** #include <eve/algo/views/map.hpp>
  //!
  //!   Has a shorthand `eve::views::map_store_op` in `<eve/views/map.hpp>`
  //! @}
  //================================================================================================

  template <typename Op, typename LoadOp, typename Base>
  concept map_store_op = std::same_as<nothing_t, Op> || (
       std::copyable<Op>
    && map_load_op<LoadOp, Base>
    && std::regular_invocable<Op, detail::map_value_type_t<LoadOp, Base>, as<value_type_t<Base>>>
    && std::regular_invocable<Op, as_wide_t<detail::map_value_type_t<LoadOp, Base>>, as<value_type_t<Base>>>);

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @struct map_iterator
  //!    @brief An iterator for `map`, `map_convert`.
  //!    Should be created with one of those functions.
  //!    If one of the operations is not avaliable, it's `eve::algo::nothing_t`.
  //!
  //!    **Required header:** `#incude <eve/algo/views/map.hpp>`
  //!
  //!    Has a shorthand `eve::views::map_iterator` in `<eve/views/map.hpp>`
  //! @}
  //================================================================================================
  template <relaxed_iterator I, map_load_op<I> LoadOp, map_store_op<LoadOp, I> StoreOp>
  struct map_iterator;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @struct map_range
  //!    @brief A range for `map`, `map_covnert`.
  //!    Should be created via one of those functions.
  //!    If the store operation is not avaliable, it's `eve::algo::nothing_t`.
  //!
  //!    **Required header:** `#incude <eve/algo/views/map.hpp>`
  //!
  //!    Has a shorthand `eve::views::map_iterator` in `<eve/views/map.hpp>`
  //! @}
  //================================================================================================
  template <non_owning_range R, map_load_op<R> LoadOp, map_store_op<LoadOp, R> StoreOp>
  struct map_range;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @var map_convert
  //!    @brief Given a relaxed iterator/range and 2 operations return
  //!    relaxed iterator/range that applies the first operation before load
  //!    and the second operation before store.
  //!
  //!    operations has to be a template and accept scalar and all width wides for the value type
  //!    of the underlying iterator/range.
  //!
  //!    store operation, for conviniece accepts the as<underlying_type> as a second parameter.
  //!    (this allows to define load/store ops without knowing the underlying iterator).
  //!
  //!    **Required header:** `#incude <eve/algo/views/map.hpp>`
  //!
  //!    Has a shorthand `eve::views::map_convert` in `<eve/views/map.hpp>`
  //! @}
  //================================================================================================
  struct
  {
    template <typename Wrapped,
              map_load_op<std::remove_cvref_t<Wrapped>> LoadOp,
              map_store_op<LoadOp, std::remove_cvref_t<Wrapped>> StoreOp>
    auto operator()(Wrapped &&wrapped, LoadOp load_op, StoreOp store_op) const
    {
      if constexpr( relaxed_range<Wrapped> )
      {
        auto rng = range_ref(std::forward<Wrapped>(wrapped));
        using Rng = decltype(rng);

        return map_range<Rng, LoadOp, StoreOp>{rng, load_op, store_op};
      }
      else
      {
        using I = std::remove_cvref_t<Wrapped>;
        return map_iterator<I, LoadOp, StoreOp>(wrapped, load_op, store_op);
      }
    }
  } map_convert;

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @var map
  //!    @brief Given a relaxed iterator/range and an operation return
  //!    relaxed iterator/range that has no store and applies provided operation on read/load.
  //!
  //!    operation has to be a template and accept scalar and all width wides for the value type
  //!    of the underlying iterator/range.
  //!
  //!    **Required header:** `#incude <eve/algo/views/map.hpp>`
  //!
  //!    Has a shorthand `eve::views::map` in `<eve/views/map.hpp>`
  //! @}
  //================================================================================================
  struct
  {
    template <typename Wrapped, map_load_op<std::remove_cvref_t<Wrapped>> LoadOp>
    auto operator()(Wrapped &&wrapped, LoadOp load_op) const
    {
      return map_convert(std::forward<Wrapped>(wrapped), load_op, nothing_t{});
    }
  } inline constexpr map;

  template <non_owning_range R, map_load_op<R> LoadOp, map_store_op<LoadOp, R> StoreOp>
  struct map_range
  {
    R base;
    LoadOp  load_op;
    StoreOp store_op;

    using is_non_owning = void;

    using types_to_consider = typename detail::map_types_to_consider<LoadOp, R>;

    EVE_FORCEINLINE auto begin() const { return map_convert(base.begin(), load_op, store_op); }
    EVE_FORCEINLINE auto end()   const { return map_convert(base.end(),   load_op, store_op); }

    template<typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr, map_range self)
    {
      auto tr2       = default_to(tr, traits {consider_types_key = types_to_consider{}});
      auto processed = preprocess_range(tr2, self.base);

      return preprocess_range_result {
          processed.traits(),
          map_convert(processed.begin(), self.load_op, self.store_op),
          map_convert(processed.end(),   self.load_op, self.store_op)
      };
    }
  };

  template <relaxed_iterator I, map_load_op<I> LoadOp, map_store_op<LoadOp, I> StoreOp>
  struct map_iterator : operations_with_distance
  {
    using value_type = detail::map_value_type_t<LoadOp, I>;
    using types_to_consider = typename detail::map_types_to_consider<LoadOp, I>;

    // need to define this to workaround a clang bug.
    using vw_type    = eve::as_wide_t<value_type, iterator_cardinal_t<I>>;

    using unaligned_me = map_iterator<unaligned_t<I>, LoadOp, StoreOp>;

    I base;
    LoadOp  load_op;
    StoreOp store_op;

    map_iterator() = default;

    EVE_FORCEINLINE map_iterator(I base, LoadOp load_op, StoreOp store_op)
        : base(base)
        , load_op(load_op)
        , store_op(store_op)
    {
    }

    template <std::convertible_to<I> I1>
    map_iterator(map_iterator<I1, LoadOp, StoreOp> x) : base(x.base),
                                                        load_op(x.load_op),
                                                        store_op(x.store_op) {}

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::unalign_, map_iterator self )
    {
      return map_convert(unalign(self.base), self.load_op, self.store_op);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::read_, map_iterator self)
      requires (!std::same_as<LoadOp, nothing_t>)
    {
      return self.load_op(eve::read(self.base));
    }

    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::write_, map_iterator self, auto v)
      requires (!std::same_as<StoreOp, nothing_t>)
    {
      eve::write(self.base, detail::bind_store_op<I>(self.store_op)(v));
    }

    template <relaxed_sentinel_for<I> I1>
    EVE_FORCEINLINE bool operator==(map_iterator<I1, LoadOp, StoreOp> y) const
    {
      return base == y.base;
    }

    template <relaxed_sentinel_for<I> I1>
    EVE_FORCEINLINE auto operator<=>(map_iterator<I1, LoadOp, StoreOp> y) const
    {
      return spaceship_helper(base, y.base);
    }

    EVE_FORCEINLINE auto& operator+=(std::ptrdiff_t n)
    {
      base += n;
      return *this;
    }

    EVE_FORCEINLINE friend std::ptrdiff_t operator-(map_iterator const & x, map_iterator const & y)
    {
      return x.base - y.base;
    }

    EVE_FORCEINLINE friend std::ptrdiff_t operator-(map_iterator const & x, unaligned_me const & y)
      requires (!std::same_as<I, unaligned_t<I>>)
    {
      return x.base - y.base;
    }

    template <typename Traits>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(preprocess_range_, Traits tr, map_iterator f, map_iterator l)
      requires (!iterator<I>)
    {
      return preprocess_range(tr, map_convert(as_range(f.base, l.base), f.load_op, f.store_op));
    }

    template <typename Traits>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(preprocess_range_, Traits tr, map_iterator f, unaligned_me l)
      requires (!iterator<I>) && (!std::same_as<I, unaligned_t<I>>)
    {
      return preprocess_range(tr, map_convert(as_range(f.base, l.base), f.load_op, f.store_op));
    }

    // eve::iterator -------------
    EVE_FORCEINLINE auto previous_partially_aligned() const
      requires iterator<I>
    {
      return map_convert(base.previous_partially_aligned(), load_op, store_op);
    }

    EVE_FORCEINLINE auto next_partially_aligned() const
      requires iterator<I>
    {
      return map_convert(base.next_partially_aligned(), load_op, store_op);
    }

    static auto iterator_cardinal() requires iterator<I>
    {
      return I::iterator_cardinal();
    }

    template <typename _Cardinal>
    EVE_FORCEINLINE auto cardinal_cast(_Cardinal N) const
      requires iterator<I>
    {
      return map_convert(base.cardinal_cast(N), load_op, store_op);
    }

    template<relative_conditional_expr C, decorator S>
      requires iterator<I> && (!std::same_as<LoadOp, nothing_t>)
    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::load_,
                                                C c,
                                                S s,
                                                eve::as<vw_type>,
                                                map_iterator self)
    {
      auto loaded =  self.load_op(eve::load(drop_alternative(c), s,
                                            self.base, eve::as<wide_value_type_t<I>>{}));
      if constexpr (C::has_alternative)
      {
        loaded = eve::replace_ignored(loaded, c, c.alternative);
      }
      return loaded;
    }

    template<relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::store_,
                                                C c,
                                                auto v,
                                                map_iterator self)
      requires iterator<I> && (!std::same_as<StoreOp, nothing_t>)
    {
      auto bound_store = detail::bind_store_op<I>(self.store_op);
      auto c1 = map_alternative( c, bound_store );
      eve::store[c1](bound_store(v), self.base);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::store_equivalent_,
                                                relative_conditional_expr auto c,
                                                auto v,
                                                map_iterator self)
      requires iterator<I> && (!std::same_as<StoreOp, nothing_t>)
    {
      auto bound_store = detail::bind_store_op<I>(self.store_op);
      auto c1 = map_alternative( c, bound_store );
      auto v1 = bound_store(v);
      return kumi::make_tuple(c1, v1, self.base);
    }
  };
}
