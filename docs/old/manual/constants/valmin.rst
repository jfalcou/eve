.. _constant-valmin:

Valmin
======

**Required header** ``#include <eve/constant/valmin.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Valmin<Value>() noexcept
   }

This 'constant' returns the lowest finite value representable by the arithmetic type `Value`.


Template parameter
------------------

 -  ``Value`` : the returned value is of type ``Value``

