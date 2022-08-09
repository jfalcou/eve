//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

//
// NOTE: another way of writing the same example can be found in: algorithms/writing_new/collect_indexes__writing_custom_loop.cpp
//
// In this example we will have a look at a problem from this blog post:
//   https://maxdemarzi.com/2021/08/30/lets-build-something-outrageous-part-13-finding-things-faster/
// This is a modified version of what they posted.
// According to the author, the number of requests per second went up 5.75 times, after using eve.
// (My understanding is that `avx2` implementation kicked in).
//
// Goal: you have a vector and a predicate. You need to return a vector of all indexes,
//       where elements match the predicate.
//
// NOTE: generally speaking SIMD and indexes are not a good match.
// Reason 1: indexes can be of bigger type, by default 64 bit, maybe 32 bit if you can.
//           this limits your SIMD capabilities.
// Reason 2: after you get the indexes, you need to do smth with those elements.
//           It's not ideal to work with multiple addresses (we have `gather` and `scatter` to do that if needed).
//           Consider just doing immediatly what you want, instead of collecting indexes.
//

#include <eve/algo/concepts.hpp>
#include <eve/algo/for_each.hpp>
#include <eve/views/iota.hpp>
#include <eve/views/zip.hpp>

#include <eve/module/core.hpp>

#include <concepts>
#include <type_traits>
#include <vector>

template <
  eve::algo::relaxed_range R, // relaxed_range is our version of the std::range
                              // concept that supports things like aligned pointers, zip, etc.
                              // ---
  typename P,                 // Predicate. Don't conceptify, since it's quite difficult (see below)
                              // and does not seem that useful.
                              // ---
  std::integral IdxType,      // Index type, should be big enough to store any element's position
                              // ---
  typename Alloc              // To not have to deal with allocators ourselves,
                              // We'll just allow you to pass a vector with any allocator.
>
void collect_indexes(R&& r, P p, std::vector<IdxType, Alloc>& res)
{
  EVE_ASSERT( (static_cast<std::size_t>(r.end() - r.begin()) <= std::numeric_limits<IdxType>::max())
            , "The output type is not big enough to hold potential indexes"
            );


  // Prepare the output in case it was not empty.
  res.clear();

  // Over allocating to always use `unsafe(compress_store)`.
  // eve won't go beyound eve::expected_cardinal_v<IdxType> per wide here.
  res.resize((r.end() - r.begin()) + eve::expected_cardinal_v<IdxType>);
  IdxType* out = res.data();

  // iota is going to be an iterator of 0, 1, 2, 3, ...
  auto idxes = eve::views::iota(IdxType{0});

  // This is a zip view of element and it's index.
  auto r_with_idx = eve::views::zip(std::forward<R>(r), idxes);

  // Tweak for each for our purposes:
  //   aligning/unrolling won't help us here due to the operation being complicated.
  //   These tweaks won't affect correctness, you can align - it will work.
  auto for_each = eve::algo::for_each[eve::algo::no_aligning][eve::algo::unroll<1>];

  // Unlike `std::for_each` which calls the predicate with a reference,
  // eve::algo::for_each calls the operations with the iterator and ignore.
  // From iterator you can load/store values and ignore is needed to mask elements
  // outside of the real range.
  //
  // The case where there is nothing to ignore is handled, there is a special `ignore_none`.
  for_each(
      r_with_idx,
      [&](eve::algo::iterator auto r_idx_it, eve::relative_conditional_expr auto ignore) mutable
      {
        // load an element and an index for each element.
        // The values in the `ignored` part are garbage.
        auto [elems, idxs] = eve::load[ignore](r_idx_it);

        // Apply the predicate
        auto test = p(elems);

        // We don't know what was the result of applying a predicate to garbage, we need to mask it.
        test = eve::replace_ignored(test, ignore, false);

        // unsafe(compress_store) - write elements marked as true to the output.
        // the elements are packed together to the left.
        // unsafe means we can write up to the register width of extra stuff.
        // returns pointer behind last written element
        //
        //  idxs    : [ 1 2 3 4 ]
        //  test    : [ f t f t ]
        //  written : [ 2 4 x x ]
        //  returns : out + 2
        out  = eve::unsafe(eve::compress_store)(idxs, test, out);
      });

  res.resize(out - res.data());
  res.shrink_to_fit();
}

// ---------------------------------------------------

#include "test.hpp"

#include <eve/algo/container/soa_vector.hpp>
#include <eve/memory/aligned_allocator.hpp>

#include "unit/algo/algo_test.hpp"

TTS_CASE("collect_indexes, elements equal to 2")
{
  std::vector<int>      input    = { 1, 1, 2, -3, 2, 10};
  std::vector<unsigned> expected = { 2, 4 };
  std::vector<unsigned> actual;
  collect_indexes(input, [](auto x) { return x == 2; }, actual);
  TTS_EQUAL(expected, actual);
};

TTS_CASE("collect_indexes for objects")
{
  using obj           = kumi::tuple<int, double>;

  eve::algo::soa_vector<obj> objects {obj{1, 2.0}, obj{-1, 2.0}, obj{1, 1}};

  std::vector<std::uint16_t> expected{0, 2};
  std::vector<std::uint16_t> idxs;
  collect_indexes(objects, [](auto x) { return get<0>(x) > 0; }, idxs);

  TTS_EQUAL(idxs, expected);
};

TTS_CASE("collect_indexes clears the result")
{
  std::vector<int>      input;
  std::vector<unsigned> expected;
  std::vector<unsigned> actual(65u);
  collect_indexes(input, [](auto x) { return x == 2; }, actual);
  TTS_EQUAL(expected, actual);
};

// ---------------
// push data through test

struct collect_indexes_generic_test
{
  std::vector<std::int64_t> expected;

  void init(auto*, auto* f, auto* l, auto*)
  {
    int count = 0;

    while (f != l) {
      if (count % 3 == 0) *f = 1;
      else                *f = 0;
      ++f;
    }
  }

  void run(auto rng)
  {
    expected.clear();
    for (auto* f = eve::unalign(rng.begin()); f != rng.end(); ++f) {
      if (*f == 1) expected.push_back(f - rng.begin());
    }

    std::vector<std::int64_t> actual;
    collect_indexes(rng, [](auto x) { return x == 1; }, actual);
    TTS_EQUAL(expected, actual);
  }

  void adjust(auto*, auto* f, auto* l, auto* page_end) const
  {
    *f = 1;
    if (l != page_end) *l = 1;
  }
};

TTS_CASE_TPL("Check collect indexes, lots", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using tgt_t = eve::wide<T, eve::fixed<eve::expected_cardinal_v<std::int64_t>>>;
  algo_test::page_ends_test(eve::as<tgt_t>{}, collect_indexes_generic_test{});
};
