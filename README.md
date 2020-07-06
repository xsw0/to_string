# to_string
All standard library containers can be converted into strings by using to_string function.
You can change the display style by modifying TO_STRING as follows

``` cpp
#include <iostream>
#include "to_string.h"

int main()
{
    std::vector<std::string> s;
    s.push_back("1");
    s.push_back("2");
    s.push_back("3");
    std::cout << to_string(s) << std::endl;
    TO_STRING::prefix<std::vector> = "[";
    TO_STRING::suffix<std::vector> = "]";
    TO_STRING::separator<std::vector> = ";";
    TO_STRING::stringPrefix = "\'";
    TO_STRING::stringSuffix = "\'";
    std::cout << to_string(s) << std::endl;
    return 0;
}
```

```
{"1", "2", "3"}
['1'; '2'; '3']
```

You can also modify the length of each line in the console.

``` cpp
#include <iostream>
#include "to_string.h"

int main()
{
    std::vector<std::string> s(10, "abc");
    std::cout << to_string(s) << std::endl;
    TO_STRING::CONSOLE_WIDTH = 10;
    std::cout << to_string(s) << std::endl;
    return 0;
}
```

it print as follow
```
{"abc", "abc", "abc", "abc", "abc", "abc", "abc", "abc", "abc", "abc"}
{
    "abc",
    "abc",
    "abc",
    "abc",
    "abc",
    "abc",
    "abc",
    "abc",
    "abc",
    "abc"
}
```

# Support list
- std::array
- std::vector
- std::deque
- std::forward_list
- std::list
- std::set
- std::map
- std::unordered_map
- std::unordered_set
- std::stack
- std::queue
- std::pair

# default format notation
``` cpp
TO_STRING::CONSOLE_WIDTH = 80;

TO_STRING::stringPrefix = "\"";
TO_STRING::stringSuffix = "\"";
TO_STRING::stringIndent = "    ";

TO_STRING::arrayPrefix = "{";
TO_STRING::arraySuffix = "}";
TO_STRING::arraySeparator = ",";
TO_STRING::arraySpace = " ";
TO_STRING::arrayNewline = "\n";
TO_STRING::arrayIndent = "    ";

TO_STRING::prefix</*other standard library container for example*/>std::vector = "{";    
TO_STRING::suffix</*other standard library container for example*/std::vector> = "}";    
TO_STRING::separator</*other standard library container for example*/std::vector> = ","; 
TO_STRING::space</*other standard library container for example*/std::vector> = " ";     
TO_STRING::newline</*other standard library container for example*/std::vector> = "\n";  
TO_STRING::indent</*other standard library container for example*/std::vector> = "    ";
```