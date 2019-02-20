.. _function-is_ltz:

is_ltz
============

**Required header** ``#include <eve/function/is_ltz.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_ltz( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is less than :ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_less <function-is_less>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Semantically equivalent to `is_less(lhs, Zero(as(lhs)))`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_ltz.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_ltz.txt
  :literal:

