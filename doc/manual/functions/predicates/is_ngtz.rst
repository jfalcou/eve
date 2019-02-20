.. _function-is_ngtz:

is_ngtz
============

**Required header** ``#include <eve/function/is_ngtz.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_ngtz( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is not greater than:ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_not_greater <function-is_not_greater>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Semantically equivalent to `is_not_greater(lhs, Zero(as(lhs)))`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_ngtz.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_ngtz.txt
  :literal:

