// revision 1
#include <eve/module/combinatorial.hpp>
#include <iostream>

eve::wide<std::uint32_t> n([](auto i, auto )->std::uint32_t{ return i+2;});
eve::wide m{13u, 25u, 32u, 80u, 1u, 2u, 3u, 4u};
eve::wide a{1.0f, 2.0f, 3.0f, 4.0f, 0.5f, 0.33f, -4.5f, 0.0f};
eve::wide b{2.0f, 3.0f, 4.0f, 0.5f, 0.33f, -4.5f, 0.0f, 1.0f};

int main(){
   std::cout << "<- n   = " << n   << "\n";
   std::cout << "<- m   = " << m   << "\n";
   std::cout << "<- a   = " << a   << "\n";
   std::cout << "<- b   = " << b   << "\n";

   std::cout << "-> fibonacci(n, 1.0f, 1.0f)= " << eve::fibonacci(n, 1.0f, 1.0f) << "\n";
   std::cout << "-> fibonacci(m, a, b)      = " << eve::fibonacci(m, a, b) << "\n";
}
