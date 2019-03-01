.. _constant-one:

One
=====

**Required header** ``#include <eve/constant/one.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> One<Value>() noexcept
   }

This 'constant' returns the  :ref:`Values <concept-value>`  0 

Template parameter
------------------

 - ``Value``  : the returned value is of type ``as_arithmetic_t<Value>``

