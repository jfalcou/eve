.. _function-is_lez:

is_lez
============

**Required header** ``#include <eve/function/is_lez.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_lez( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is less or equal to :ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_equal <function-is_equal>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Semantically equivalent to `is_less_equal(lhs, Zero(as(lhs)))`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_lez.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_lez.txt
  :literal:

