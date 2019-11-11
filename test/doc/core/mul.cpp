#include <eve/function/mul.hpp>
#include <eve/literals.hpp>
#include <eve/wide.hpp>

int main()
{
  using namespace eve::literal;
  eve::wide<float, eve::fixed<4>> w([](auto i, auto) { return 1.f + i; });
  std::cout << "mul(3.f, 5.5f) = " << eve::mul(3.f, 5.5f) << '\n';
  std::cout << "3._wf  = " << 3._wf << std::endl;
  std::cout << "w      = " << w << std::endl;
  std::cout << "mul(3._wf, w) = " << eve::mul(3.f, w) << '\n';
}
