By default, conditional operations use their unchanged input whenever the conditional
evaluates to `false`. By using this member function, operations will use the user provided
eve::value `v` instead.

@param  v Value to use if the conditional expression evaluates to `false`

@return An instance of eve::or_ wrapping current conditional expression with `v`.
