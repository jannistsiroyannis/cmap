/*******************************************************************************
Copyright (c) 2016 Jannis Mohlin Tsiroyannis

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 ******************************************************************************/

/*
Output of this program:
Map had "Some string key" mapped to 1
Map had "Another string key" mapped to 2
 */


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
