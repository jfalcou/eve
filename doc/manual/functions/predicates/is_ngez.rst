.. _function-is_ngez:

is_ngez
============

**Required header** ``#include <eve/function/is_ngez.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_ngez( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is not greater or equal to :ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_not_greater_equal <function-is_not_greater_equal>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Semantically equivalent to ``is_not_greater_equal(lhs, Zero(as(lhs)))``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_ngez.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_ngez.txt
  :literal:

