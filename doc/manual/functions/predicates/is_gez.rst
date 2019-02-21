.. _function-is_gez:

is_gez
============

**Required header** ``#include <eve/function/is_gez.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_gez( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is greater or equal to :ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_equal <function-is_equal>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Semantically equivalent to ``is_greater_equal(lhs, Zero(as(lhs)))``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_gez.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_gez.txt
  :literal:

