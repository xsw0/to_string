#include "to_string.h"

std::string TO_STRING::emptyString;

size_t TO_STRING::CONSOLE_WIDTH = 80;

std::string TO_STRING::stringPrefix = "\"";
std::string TO_STRING::stringSuffix = "\"";
std::string TO_STRING::stringIndent = "    ";

std::string TO_STRING::arrayPrefix = "{";
std::string TO_STRING::arraySuffix = "}";
std::string TO_STRING::arraySeparator = ",";
std::string TO_STRING::arraySpace = " ";
std::string TO_STRING::arrayNewline = "\n";
std::string TO_STRING::arrayIndent = "    ";

#define DEFAULT(container)                             \
    template <>                                        \
    std::string TO_STRING::prefix<container> = "{";    \
    template <>                                        \
    std::string TO_STRING::suffix<container> = "}";    \
    template <>                                        \
    std::string TO_STRING::separator<container> = ","; \
    template <>                                        \
    std::string TO_STRING::space<container> = " ";     \
    template <>                                        \
    std::string TO_STRING::newline<container> = "\n";  \
    template <>                                        \
    std::string TO_STRING::indent<container> = "    ";

DEFAULT(std::vector);
DEFAULT(std::deque);
DEFAULT(std::forward_list);
DEFAULT(std::list);
DEFAULT(std::set);
DEFAULT(std::map);
DEFAULT(std::multiset);
DEFAULT(std::multimap);
DEFAULT(std::unordered_set);
DEFAULT(std::unordered_map);
DEFAULT(std::unordered_multiset);
DEFAULT(std::unordered_multimap);
DEFAULT(std::stack);
DEFAULT(std::queue);

DEFAULT(std::pair);
#undef DEFAULT

