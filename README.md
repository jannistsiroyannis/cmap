# cmap
A generic, typed, single-header, hashmap implementation in C.

## Memory policy:
Insertion causes a struct assignment (=) into an internal buffer, owned and maintained by the map itself. If your type is (or contains) a pointer or other resource that needs to be freed, you yourself are of course responsible for freeing that resource when appropriate.

## Declaration instruction:
There are two macros that need to expanded into your code to use this library
_DECLARE_MAP( V, K, SN, FN )
_IMPLEMENT_MAP( V, K, SN, FN, C, H  )

* _DECLARE_MAP can and should be expanded in any c/header files where maps of this particular type are to be used.
* _IMPLEMENT_MAP should only be expanded in exactly ONE c file in your code. Multiples of this macro will result in linking problems.

The parameters of the macros are as follows:

* V : The TYPE of values in the map
* K : The TYPE of keys in the map
* SN : the TYPENAME of the map object itself (must begin with "struct ").
* FN : the prefix to use for functions accessing this type of map.
* C : A function pointer to a comparison-function for your key type. The function must have the following signature: `int function ( const K * key0, const K * key1 )` The function must return 0 on equality.
* H : a hash function for your key type. The function must have the following signature: `unsigned hash(const K* str)`.


## Example usage:
see example.c

```c
#include <string.h>
#include <stdio.h>
#include "map_template.h"

// A hash function for whatever type is used as KEYS
static unsigned string_hash(const char* str)
{
   unsigned result = 0;
   unsigned exponent = 1;
   while(*str != '\0')
   {
      result += *(str++) * exponent;
      exponent *= 2;
   }
   return result;
}

// In header files needing access to the map:
_DECLARE_MAP(int, const char*, struct StrMap, str_map)

// In ONE c file:
_IMPLEMENT_MAP(int, const char*, struct StrMap, str_map, strcmp, string_hash)

int main()
{
   // Create a table, with initial size 10 and dynamically growing
   struct StrMap map = str_map_create(10, 1);

   // Insert data
   const char* key0 = "Some string key";
   const char* key1 = "Another string key";
   str_map_insert(&map, 1, key0);
   str_map_insert(&map, 2, key1);

   // Get data
   int value0;
   int value1;
   if ( str_map_get(&map, key0, &value0) == 0 )
      printf("Map had \"%s\" mapped to %d\n", key0, value0);
   if ( str_map_get(&map, key1, &value1) == 0 )
      printf("Map had \"%s\" mapped to %d\n", key1, value1);

   return 0;
}
```
