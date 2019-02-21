.. _function-is_nan:

is_nan
======

**Required header** ``#include <eve/function/is_nan.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_nan( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is nan

.. seealso::  :ref:`Nan <constant-nan>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``is_not_equal(lhs, lhs)``.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_nan.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_nan.txt
  :literal:

