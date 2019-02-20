.. _constant-true_:

True
=====

**Required header** ``#include <eve/constant/true.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> True<Value>() noexcept
   }

This 'constant' returns the  :ref:`Values <concept-value>` corresponding to true


.. seealso::  :ref:`False <constant-false_>`,  :ref:`Zero <constant-zero>`

Parameters
----------

  - Value template type : the returned truth value is of type s_logical_t<Value>

