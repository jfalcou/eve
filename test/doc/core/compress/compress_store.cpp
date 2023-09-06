#include <eve/module/core.hpp>
#include <tts/tts.hpp>

using n = eve::fixed<4>;
using w_t = eve::wide<int, n>;
using l_t = eve::logical<eve::wide<std::uint8_t, n>>; // Note the type mismatch

int main()
{
  w_t in { 1,     2,      3,      4 };
  l_t m  { false, true, true, false };

  {
    // We have to have 4 elements in the output, even if only 2 are selected.
    std::array<int, 4> out {};

    int* o = eve::compress_store[eve::unsafe](in, m, out.data());
    TTS_EQUAL(2, o - out.data());  // 2 elements are selected and written

    // We don't know what elements are after
    out[2] = -1;
    out[3] = -1;
    TTS_EQUAL((std::array{2, 3, -1, -1}), out);
  }

  {
    // Here we know we won't write more than selected,
    // at the price of it being more expensive
    std::array<int, 2> out {};
    int* o = eve::compress_store[eve::safe](in, m, out.data());

    TTS_EQUAL(o - out.data(), 2);
    TTS_EQUAL((std::array{2, 3}), out);
  }

  {
    // Ignore output defaults to the input ignore.
    std::array<int, 3> out {-1, 0, 0};
    int* o = eve::compress_store[eve::unsafe][eve::keep_between(1, 3)](in, m, out.data());

    TTS_EQUAL(o - out.data(), 3);
    TTS_EQUAL((std::array{-1, 2, 3}), out);
  }

  {
    // But can be separate
    std::array<int, 3> out {0, -1, -1};
    int* o = eve::compress_store[eve::unsafe][eve::ignore_none][eve::keep_first(1)](in, m, out.data());
    TTS_EQUAL(o - out.data(), 1);
    TTS_EQUAL((std::array{2, -1, -1}), out);
  }
}
