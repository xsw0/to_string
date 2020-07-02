#ifndef __TO_STRING_H__
#define __TO_STRING_H__

#include <string>

#include <array>
// #include <vector>
// #include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

namespace TO_STRING
{
    extern std::string emptyString;

    extern size_t CONSOLE_WIDTH;

    extern std::string stringPrefix;
    extern std::string stringSuffix;
    extern std::string stringIndent;

    extern std::string arrayPrefix;
    extern std::string arraySuffix;
    extern std::string arraySeparator;
    extern std::string arraySpace;
    extern std::string arrayNewline;
    extern std::string arrayIndent;

    template <template <typename...> class>
    int prefix;
    template <template <typename...> class>
    int suffix;
    template <template <typename...> class>
    int separator;
    template <template <typename...> class>
    int space;
    template <template <typename...> class>
    int newline;
    template <template <typename...> class>
    int indent;

#define DEFAULT(container)                   \
    template <>                              \
    extern std::string prefix<container>;    \
    template <>                              \
    extern std::string suffix<container>;    \
    template <>                              \
    extern std::string separator<container>; \
    template <>                              \
    extern std::string space<container>;     \
    template <>                              \
    extern std::string newline<container>;   \
    template <>                              \
    extern std::string indent<container>;

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
} // namespace TO_STRING

inline std::string operator*(const std::string &s, size_t times)
{
    std::string result;
    result.reserve(s.size() * times);
    for (size_t i = 0; i < times; i++)
    {
        result += s;
    }
    return result;
}

inline std::string operator*(size_t times, const std::string &s)
{
    return s * times;
}

inline std::string tolower(const std::string &s)
{
    std::string result(s);
    for (auto &x : result)
    {
        x = std::tolower(x);
    }
    return result;
}

inline std::string toupper(const std::string &s)
{
    std::string result(s);
    for (auto &x : result)
    {
        x = std::toupper(x);
    }
    return result;
}

inline std::string to_string(const std::string &s,
                             std::string &indents = TO_STRING::emptyString)
{
    return indents + std::string(TO_STRING::stringPrefix) + s + std::string(TO_STRING::stringSuffix);
}

template <typename T>
std::string to_string(const T &x,
                      std::string &indents = TO_STRING::emptyString);

template <typename... T>
std::string to_string(const std::pair<T...> &p,
                      std::string &indents = TO_STRING::emptyString);

template <typename T, size_t size>
std::string to_string(const std::array<T, size> &arr,
                      std::string &indents = TO_STRING::emptyString);

template <template <typename...> class T, typename ForwardIt>
std::string to_string(ForwardIt first,
                      ForwardIt last,
                      std::string &indents = TO_STRING::emptyString);

#define DeclForwardItContainer(container)           \
    template <typename... T>                        \
    std::string to_string(const container<T...> &x, \
                          std::string &indents = TO_STRING::emptyString);

DeclForwardItContainer(std::vector);
DeclForwardItContainer(std::deque);
DeclForwardItContainer(std::forward_list);
DeclForwardItContainer(std::list);
DeclForwardItContainer(std::set);
DeclForwardItContainer(std::map);
DeclForwardItContainer(std::multiset);
DeclForwardItContainer(std::multimap);
DeclForwardItContainer(std::unordered_set);
DeclForwardItContainer(std::unordered_map);
DeclForwardItContainer(std::unordered_multiset);
DeclForwardItContainer(std::unordered_multimap);
#undef DeclForwardItContainer

template <typename T>
std::string to_string(const T &x, std::string &indents)
{
    return indents + std::to_string(x);
}

#define ForwardItContainer(container)                                          \
    template <typename... T>                                                   \
    std::string to_string(const container<T...> &x, std::string &indents)      \
    {                                                                          \
        return to_string<container,                                            \
                         typename container<T...>::const_iterator>(x.cbegin(), \
                                                                   x.cend(),   \
                                                                   indents);   \
    }

ForwardItContainer(std::vector);
ForwardItContainer(std::deque);
ForwardItContainer(std::forward_list);
ForwardItContainer(std::list);
ForwardItContainer(std::set);
ForwardItContainer(std::map);
ForwardItContainer(std::multiset);
ForwardItContainer(std::multimap);
ForwardItContainer(std::unordered_set);
ForwardItContainer(std::unordered_map);
ForwardItContainer(std::unordered_multiset);
ForwardItContainer(std::unordered_multimap);
#undef ForwardItContainer

template <typename... T>
std::string to_string(const std::pair<T...> &p,
                      std::string &indents)
{
    using namespace TO_STRING;
    std::string result;

    result += indents;
    result += prefix<std::pair>;
    {
        std::string s;
        result += to_string(p.first, s);
    }
    result += separator<std::pair>;
    result += space<std::pair>;
    {
        std::string s;
        result += to_string(p.second, s);
    }
    result += suffix<std::pair>;

    if (result.size() < CONSOLE_WIDTH)
    {
        return result;
    }
    else
    {
        std::string result;
        result += indents;
        result += prefix<std::pair>;
        result += newline<std::pair>;
        indents += indent<std::pair>;
        result += to_string(p.first, indents);
        result += separator<std::pair>;
        result += newline<std::pair>;
        result += to_string(p.second, indents);
        result += separator<std::pair>;
        result += newline<std::pair>;
        indents.erase(indents.size() - indent<std::pair>.size());
        result += indents;
        result += suffix<std::pair>;
        return result;
    }
}

template <typename T, size_t size>
std::string to_string(const std::array<T, size> &arr, std::string &indents)
{
    using namespace TO_STRING;
    if (arr.cbegin() == arr.cend())
    {
        return indents + arrayPrefix + arraySuffix;
    }
    else
    {
        std::string result;
        result += indents;
        result += arrayPrefix;
        auto it = arr.cbegin();
        for (; std::next(it) != arr.cend(); ++it)
        {
            std::string s;
            result += to_string(*it, s);
            result += arraySeparator;
            result += arraySpace;
        }
        std::string s;
        result += to_string(*it, s);
        result += arraySuffix;

        if (result.size() < CONSOLE_WIDTH)
        {
            return result;
        }
        else
        {
            std::string result(indents + arrayPrefix + arrayNewline);
            indents += arrayIndent;
            auto it = arr.cbegin();
            for (; std::next(it) != arr.cend(); ++it)
            {
                result += to_string(*it, indents);
                result += arraySeparator;
                result += arrayNewline;
            }
            result += to_string(*it, indents);
            result += arrayNewline;
            indents.erase(indents.size() - arrayIndent.size());
            return result + indents + arraySuffix;
        }
    }
}

template <template <typename...> class T, typename ForwardIt>
std::string to_string(ForwardIt first,
                      ForwardIt last,
                      std::string &indents)
{
    using namespace TO_STRING;
    if (first == last)
    {
        return indents + prefix<T> + suffix<T>;
    }
    else
    {
        std::string result;
        result += indents;
        result += prefix<T>;
        auto it = first;
        for (; std::next(it) != last; ++it)
        {
            std::string s;
            result += to_string(*it, s);
            result += separator<T>;
            result += space<T>;
        }
        std::string s;
        result += to_string(*it, s);
        result += suffix<T>;

        if (result.size() < CONSOLE_WIDTH)
        {
            return result;
        }
        else
        {
            std::string result(indents + prefix<T> + newline<T>);
            indents += indent<T>;
            auto it = first;
            for (; std::next(it) != last; ++it)
            {
                result += to_string(*it, indents);
                result += separator<T>;
                result += newline<T>;
            }
            result += to_string(*it, indents);
            result += newline<T>;
            indents.erase(indents.size() - indent<T>.size());
            return result + indents + suffix<T>;
        }
    }
}

#endif
