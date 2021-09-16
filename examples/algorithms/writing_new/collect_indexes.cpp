//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

//
// In this example we will have a look at a problem from this blog post:
//   https://maxdemarzi.com/2021/08/30/lets-build-something-outrageous-part-13-finding-things-faster/
// This is a slightly modified version of what they posted.
// Accroding to the author, the number of requests per second went up 5.75 times, after using eve.
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
#include <eve/algo/preprocess_range.hpp>

#include <eve/function/compress_store.hpp>
#include <eve/function/load.hpp>

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
  EVE_ASSERT((r.end() - r.begin() <= std::numeric_limits<IdxType>::max()),
              "The output type is not big enough to hold potential indexes");

  // Prepare the output in case it was not empty.
  res.clear();

  // We have to do this everywhere in `algo`.
  // There is a requirement for `eve::load` that the pointer/iterator is to
  // somewheere in valid memory, even if we ignore everything.
  if (r.begin() == r.end()) return;

  using T = eve::algo::value_type_t<std::remove_cvref_t<R>>;

  // As a step we should use the minimum cardinal between what T and IdxType.
  // (at least by default).
  // Otherwise either the compressing of the output or applying the predicate will be weird.
  constexpr std::ptrdiff_t step = std::min(eve::expected_cardinal_v<T>,
                                           eve::expected_cardinal_v<IdxType>);

  // This converts the input to eve's understanding of a range:
  // unwraps vector::iterator to pointers, things like that.
  auto processed = eve::algo::preprocess_range(
    eve::algo::traits{eve::algo::force_cardinal<step>},
    std::forward<R>(r)
  );

  // Here we would normally use `for_each_iteration` but it's good to understand what's
  // happening inside.
  auto f         = processed.begin();
  auto l         = processed.end();
  auto precise_l = f + (l - f) / step * step;

  // We are going to overallocate the output so that we can don't have to store partial
  // registers
  res.resize(l - f + step);

  IdxType* out = res.data();  // where will we write the data

  // In a normal loop this would be i from for (i = 0; i != ...)
  // The lambda constructor will fill in (0, 1, 2, ...);
  eve::wide<IdxType, eve::fixed<step>> wide_i{[](int i, int) { return i; }};

  while (f != precise_l) {
    auto test     = p(eve::load(f));  // apply the predicate
    auto idx_test =
      eve::convert(test, eve::as<eve::logical<IdxType>>{});  // At the moment we need to convert
                                                             // the logical types. We plan on fixing this.

    // Compress store is the working horse of `remove`. It get's values, mask and where to store.
    // Writes all of the elements, for which mask is true.
    // Returns a pointer to after the last stored.
    // `unsafe` refers to the fact that it's allowed to store up to the whole register,
    // as long as the first elements are fine.
    out = eve::unsafe(eve::compress_store)(wide_i, idx_test, out);

    wide_i += step;  // ++i
    f      += step;  // ++f
  }

  // Deal with tail
  if (f != l) {
    auto ignore   = eve::keep_first(l - f);  // elements after l should not be touched
    auto test     = p(eve::load[ignore](f)); // This will safely load the partial register.
                                             // The last elements that correspond to after l will be garbage.
    auto idx_test = eve::convert(test, eve::as<eve::logical<IdxType>>{});

    // We have overallocated the output, but we still need to mask out garbage elements
    idx_test = idx_test && ignore.mask(eve::as(idx_test));
    out = eve::unsafe(eve::compress_store)(wide_i, idx_test, out);
  }

  // Clean up the vector
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
}

TTS_CASE("collect_indexes for objects")
{
  using obj           = kumi::tuple<int, double>;

  eve::algo::soa_vector<obj> objects {obj{1, 2.0}, obj{-1, 2.0}, obj{1, 1}};

  std::vector<std::uint16_t> expected{0, 2};
  std::vector<std::uint16_t> idxs;
  collect_indexes(objects, [](auto x) { return get<0>(x) > 0; }, idxs);

  TTS_EQUAL(idxs, expected);
}

TTS_CASE("collect_indexes clears the result")
{
  std::vector<int>      input;
  std::vector<unsigned> expected;
  std::vector<unsigned> actual(65u);
  collect_indexes(input, [](auto x) { return x == 2; }, actual);
  TTS_EQUAL(expected, actual);
}

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
    for (auto* f = eve::algo::unalign(rng.begin()); f != rng.end(); ++f) {
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

EVE_TEST_TYPES("Check collect indexes, lots", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using tgt_t = eve::wide<T, eve::fixed<eve::expected_cardinal_v<std::int64_t>>>;
  algo_test::page_ends_test(eve::as<tgt_t>{}, collect_indexes_generic_test{});
};
