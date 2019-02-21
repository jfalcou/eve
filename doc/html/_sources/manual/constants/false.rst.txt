.. _constant-false_:

False
=====

**Required header** ``#include <eve/constant/false.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> False<Value>() noexcept
   }

This 'constant' returns the  :ref:`Values <concept-value>` corresponding to false


.. seealso::  :ref:`True <constant-true_>`,  :ref:`Zero <constant-zero>`

Parameters
----------

  - Value template type : the returned false value is of type as_logical_t<Value>

