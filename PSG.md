#Programming Style Guidelines#

This guideline is based on [Geotechnical Software Services C++ Programming Style Guidelines](http://geosoft.no/development/cppstyle.html), but with some additions and modifications.

###Naming Conventions###

In my projects I will be using CamelCase. Variables will be named starting with lowercase letter, whereas functions starting with uppercase. Variables should have meaningful names, short names like `i, j, k` are only allowed for variables with small scope or structures like `PAINTSTRUCT ps; RECT rct;`.

* `variable` --- camelCase
* `function` --- CamelCase
* `#define`  --- SNAKE_CASE

###Indentation###

* indent with tabs of size 4
* Use Allman indentation style
* This is acceptable:
`if(condition){//one short statement}`
* If list of parameters is very long I will break it into several lines, each line starting one space to the right of opening bracket. Moreover, I will leave free space before and after such functions.

