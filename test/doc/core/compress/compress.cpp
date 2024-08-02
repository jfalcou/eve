#include <eve/module/core.hpp>
#include <tts/tts.hpp>

// template to make if constexpr not activate
template <typename T>
void show_return_type(T)
{
  if constexpr (std::same_as<T, std::int8_t> && eve::current_api == eve::sse4_2)
  {
    // On sse4_2 the default wide<std::int8_t>::size() == 16

    // We cannot compress 16 bytes in one step,
    // We need to split it into 2 chunks of 8.
    //
    // So the result will be 2 chunks of 8.
    // We will also return how many are in each chunk

    // clang-format off
    eve::wide<T> in {
       1,  2,  0,  4, //
       5,  0,  6,  7, //
       8,  9, 10, 11, //
      12,  0, 14, 15, //
    };
    // clang-format on

    using i8x8 = eve::wide<std::int8_t, eve::fixed<8>>;

    using chunk = kumi::tuple<i8x8, int>;  // int should be ptrdiff_t - this is a bug

    // ignore will be interpreted as false in the mask
    kumi::tuple<chunk, chunk> compressed = eve::compress[eve::ignore_first(1)](in, in != 0);

    auto [lo, hi] = compressed;

    auto [lo_compressed, lo_count] = lo;
    auto [hi_compressed, hi_count] = hi;

    TTS_EQUAL(5, lo_count); // 2 zeroes in the first 8 elements + ignore_first
    TTS_EQUAL(7, hi_count); // 1 zero in the second 8 elements

    // The 'tail' after removed elements is unspecified
    // so looking at them is not helpful.
    lo_compressed.set(5, -1);
    lo_compressed.set(6, -1);
    lo_compressed.set(7, -1);
    hi_compressed.set(7, -1);

    TTS_EXPECT(eve::all(lo_compressed == i8x8{2, 4, 5, 6, 7, -1, -1, -1}));
    TTS_EXPECT(eve::all(hi_compressed == i8x8{8, 9, 10, 11, 12, 14, 15, -1}));
  }
}

// Here is how one can use `eve::compress` directly.
// This how for some platforms we can implement `compress_copy_unsafe_dense`.
int* compress_copy_using_compress_directly(const int* in, int* out)
{
  auto loaded = eve::load(in);

  // a tuple or compressed wides.
  // each part is not just a wide but is a tuple<wide, count>
  // so that you know how to compact values after
  //
  // So using chunk = kumi::tuple<wide<int, N1>>;
  // So kumi::tuple<chunk, ...>
  kumi::tuple compressed_whole = eve::compress(loaded, loaded != 0);

  kumi::for_each([&](auto compressed_lengh) {
    auto [compressed, length] = compressed_lengh;
    eve::store(compressed, out);
    out += length;
  }, compressed_whole);

  return out;
}

void validate_compress_copy(auto f)
{
  constexpr std::size_t N = eve::wide<int>::size();
  std::array<int, N> in = {};

  for (std::size_t i = 0; i != N; ++i) {
    if (i % 4 == 0) in[i] = 0;
    else
    {
      in[i] = i;
    }
  }

  std::array<int, N> expected = {};
  std::copy_if(in.begin(), in.end(), expected.begin(), [](int x) { return x != 0; });

  std::array<int, N> out = {};
  auto* o = f(in.data(), out.data());
  std::fill(o, out.data() + out.size(), 0);

  TTS_EQUAL(expected, out);
}

int main()
{
  show_return_type(std::int8_t{0});
  validate_compress_copy(compress_copy_using_compress_directly);
}
