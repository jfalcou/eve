.. _constant-zero:

Zero
=====

**Required header** ``#include <eve/constant/zero.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Zero<Value>() noexcept
   }

This 'constant' returns the  :ref:`Values <concept-value>`  0 

Parameters
----------

 - Value template type : the returned 0 is of type Value

