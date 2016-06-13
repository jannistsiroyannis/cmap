# cmap
A generic, typed, single-header, hashmap implementation in C.

## Memory policy:
Insertion causes a struct assignment (=) into an internal buffer, owned and maintained by the map itself. If your type is (or contains) a pointer or other resource that needs to be freed, you yourself are of course responsible for freeing that resource when appropriate.

## Declaration instruction:
There are two macros that need to expanded into your code to use this library
_DECLARE_MAP( V, K, SN, FN )
_IMPLEMENT_MAP( V, K, SN, FN, C, H  )

* _DECLARE_MAP can and should be expanded in any c/header files where maps are to be used.
* _IMPLEMENT_MAP should only be expanded in exactly ONE c file in your code. Multiples of this macro will result in linking problems.

The parameters of the macros are as follows:

* V : The TYPE of values in the map
* K : The TYPE of keys in the map
* SN : the TYPENAME of the map object itself (must begin with "struct ").
* FN : the prefix to use for functions accessing this type of map.
* C : A function pointer to a comparison-function for your KEY type. The function must have the following signature: `int function ( const K * key0, const K * key1 )` The function must return 0 on equality.
* H : a hash function for your key type. The function must have the following signature: `unsigned hash(const K* str)`.


## Example usage:
see example.c
