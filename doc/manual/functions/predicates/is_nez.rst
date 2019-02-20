.. _function-is_nez:

is_nez
============

**Required header** ``#include <eve/function/is_nez.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_nez( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is not equal to :ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_not_equal <function-is_equal>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Semantically equivalent to `is_not_equal(lhs, Zero(as(lhs)))`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_nez.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_nez.txt
  :literal:

