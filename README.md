# RecursiveDescentParserForNestedIf
A simple recursive descent parser for accepting all  nested-if commands implemented in C.

## Input
The input for the program is given in the format:

```
if ( c ) { if ( c ) {...if ( c ) { stmt ; } else { stmt ; }...} else { stmt ; } } else { stmt; }

```

## Grammar
The grammar for nested-if used is given below. The code is implemented using the following grammar:

```
S' --> S | SS'
S --> B | B else { S } | A
B --> if ( c ) { S }
A --> stmt;
```

## Running code
The code is written in C and can be run in terminal using the following commands:
```
>gcc rdpnestedif.c -o rdp
>./rdp
```
## Output
<img width="410" alt="image" src="https://user-images.githubusercontent.com/68645801/183091425-d6d806c2-0a48-4dbb-ba28-b707b4becbaa.png">
