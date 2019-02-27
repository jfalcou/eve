.. _constant-mzero:

Mzero
=====

**Required header** ``#include <eve/constant/mzero.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Mzero<Value>() noexcept
   }

This 'constant' returns the  :ref:`Values <concept-value>` -0, that is 0 for Integral types, but responding true to 
:ref:`is_negative <function-is_negative>` for floating point types.

Template parameter
------------------

 -  ``Value``: the returned value is of type ``Value``

