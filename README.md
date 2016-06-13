# cmap
A generic, typed, single-header, hashmap implementation in C.

## Memory policy:
Insertion causes a struct assignment (=) into an internal buffer, owned and maintained by the map itself. If your type is (or contains) a pointer or other resource that needs to be freed, you yourself are of course responsible for freeing that resource when appropriate.
 
## Example usage:
see example.c
