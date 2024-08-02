#include <eve/module/core.hpp>

#include <tts/tts.hpp>

using n    = eve::fixed<4>;
using i32s = eve::wide<int, n>;
using f64s = eve::wide<double, n>;

template<typename T>
concept iota_supports = std::invocable<decltype(eve::iota), eve::as<T>>;

// See below - maybe this is what you are looking for?
void how_to_keep_track_of_index();

int main()
{
  how_to_keep_track_of_index();

  // basic ints
  {
    i32s expected {0, 1, 2, 3};
    i32s actual = eve::iota(eve::as<i32s> {});
    TTS_EXPECT(eve::all(expected == actual));
  }

  // floats
  {
    f64s expected {0.0, 1.0, 2.0, 3.0};
    f64s actual = eve::iota(eve::as<f64s> {});
    TTS_EXPECT(eve::all(expected == actual));
  }

  // doesn't work for
  {
    static_assert(!iota_supports<eve::logical<i32s>>);
    static_assert(!iota_supports<eve::logical<int>>);
  }

  // conditional
  {
    auto       tgt     = eve::as<i32s> {};
    const auto actual0 = eve::iota[eve::ignore_last(2)](tgt);
    const auto actual1 = eve::iota[eve::ignore_last(2).else_(5)](tgt);

    TTS_EXPECT(eve::all(actual0 == i32s {0, 1, 0, 0}));
    TTS_EXPECT(eve::all(actual1 == i32s {0, 1, 5, 5}));

    const auto m       = eve::logical<i32s> {true, true, false, false};
    const auto actual2 = eve::iota[m](tgt);
    const auto actual3 = eve::iota[eve::if_(m).else_(5)](tgt);

    TTS_EXPECT(eve::all(actual2 == i32s {0, 1, 0, 0}));
    TTS_EXPECT(eve::all(actual3 == i32s {0, 1, 5, 5}));
  }
}

#include <eve/module/algo.hpp>

void
how_to_keep_track_of_index()
{
  // There is a good chance you found this doc because
  // you wanted to enumerate all elements in a sequence.

  // It is harder then you might think in a general case.
  // If you need to do it for small types (such as vector of chars or shorts)
  // look at `eve::algo::for_each_iteration_fixed_overflow`.
  // There is no docs for that at this point, because it is very clumsy.

  // If you don't care about overflow, just zip with iota view.

  // Example: for (int i = 0; auto& x : v) x = (i++) * 2;
  {
    std::vector<int> v;
    v.resize(10);

    eve::algo::transform_to(
        eve::views::iota(0), v, [](eve::like<int> auto idx) { return idx + idx; });

    TTS_EQUAL(v, std::vector<int>({0, 2, 4, 6, 8, 10, 12, 14, 16, 18}));
  }

  // Example: imperfect for (int i = 0; auto& x : v) x = x << i;
  {
    std::vector<int> v(5u, 1);

    // Here, because we pass v twice, it will not be as perfect as it can but
    // it has advantage of being very simple.
    eve::algo::transform_to(eve::views::zip(v, eve::views::iota(0)),
                            v,
                            [](auto input_idx)
                            {
                              auto [input, idx] = input_idx;
                              return input << idx;
                            });

    TTS_EQUAL(v, std::vector<int>({1, 2, 4, 8, 16}));
  }

  // Example: handwriting for (int i = 0; auto& x : v) x = x << i;
  {
    std::vector<int> v(5u, 1);
    eve::algo::for_each(eve::views::zip(v, eve::views::iota(0)),
                        [](eve::algo::iterator auto it, eve::relative_conditional_expr auto ignore)
                        {
                          auto [elements_it, index_it] = it;
                          eve::like<int> auto elements = eve::load[ignore](elements_it);
                          eve::like<int> auto idxs     = eve::load[ignore](index_it);

                          elements <<= idxs;
                          eve::store[ignore](elements, elements_it);
                        });
    TTS_EQUAL(v, std::vector<int>({1, 2, 4, 8, 16}));
  }
}
