.. _function-is_gtz:

is_gtz
============

**Required header** ``#include <eve/function/is_gtz.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_gtz( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is greater than:ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_equal <function-is_equal>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Semantically equivalent to `is_greater(lhs, Zero(as(lhs)))`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_gtz.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_gtz.txt
  :literal:

