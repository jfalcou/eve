.. _constant-nan:

Nan
====

**Required header** ``#include <eve/constant/nan.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_arithmetic_t<Value> Nan<Value>() noexcept
   }

This 'constant' returns the  :ref:`Values <concept-value>` Not a Number for  :ref:`floating point Values <concept-IEEEvalue>` 
and zero for  :ref:`Integral typed Values <concept-integralvalue>`


Parameters
----------

 - Value template type : the returned false value is of type as_logical_t<Value>

