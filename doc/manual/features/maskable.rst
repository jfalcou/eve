.. _feature-maskable:

Maskable
========

:ref:`feature-maaskable` is a feature dedicated to simd operations that allow to choose the elements of an simd wide
on which  a function object can be applied **masking** the other ones.

Syntax
------

  If  ``func`` an **EVE** object function object that is maskable and ``cond`` a condition
  a call to ``func_(x, ...)`` can be replaced by ``func_[cond](x, ...)``.

  This last call is semantically equivalent to ``if_else(cond, func_(x, ...), T(x))``
  where ``T`` is ``decltype(func_(x, ...))``. (In particular this feature is not available if ``x``
  is not convertible to ``T``).

