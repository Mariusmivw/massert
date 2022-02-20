# massert
MariusAssert / MatureAssert / MegaAssert / MightyAssert / MindfulAssert / MultipleAssert / MyAssert

An assert that automatically detect the type of its arguments ad compares them (if they're of the same type). Extensible with custom types.

## Usage
### Compilation
* First build project from source (`make`)
* Copy `libmassert.a` and `massert.h` to a location of choice
* Compile using: `gcc ... -L[Directory of libmassert.a] -lmassert -I[Directory of massert.h]` (not including the `[]` around the directory names)

### Definitions
`massert`:
* Usage: `massert(value1, value2);`
* Trigger abort when the two values are different
* You can add your own types by defining `custom_assert_types`
* Example: `massert("hello", "world");`

`custom_assert_types`:
* Add your own types by using `add_assert_type(type, eq_fn, str_fn)` (each call seperated by whitespace)
* Example:
```c
#define custom_assert_types                             \
	add_assert_type(void *, compare_ptrs, ptr_as_str)   \
	add_assert_type(int, compare_ints, int_as_str)
```

`add_assert_type`:
* Usage: `add_assert_type(type, eq_fn, str_fn)`
* It is recommended to not add structs as types, you should use pointers to structs instead
* Params:
  * `type`: The type to add a definition for
  * `eq_fn` The function (t_massert_eq_fn) which checks whether the two inputs are the same
  * `str_fn` The function (t_massert_str_fn) to convert the argument to a (c) string
* Example: `add_assert_type(void *, compare_ptrs, ptr_as_str)`

## Building from source
To compile libmassert.a use: `make all`
