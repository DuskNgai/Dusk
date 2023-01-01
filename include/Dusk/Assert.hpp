#ifndef _DUSK_ASSERT_HPP_
#define _DUSK_ASSERT_HPP_

#include <stdexcept>

#define DUSK_EXPAND_MACRO(x) x
#define _DUSK_STRINGIFY_MACRO_(x) #x
#define DUSK_STRINGIFY_MACRO(x) _DUSK_STRINGIFY_MACRO_(x)
#define DUSK_FILE_AND_LINE "file " __FILE__ " line " DUSK_STRINGIFY_MACRO(__LINE__)

// Alteratively we could use the same "default" message for both "WITH_MSG" and "WITHOUT_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define _DUSK_INTERNAL_ASSERT_IMPL_(type, check, msg, ...)                                                      \
    do {                                                                                                        \
        if (!(check)) {                                                                                         \
            throw std::runtime_error{                                                                           \
                std::string("DUSK" #type "ERROR: " DUSK_FILE_AND_LINE ": assert `" #check "` failed. ") + msg}; \
        }                                                                                                       \
    } while (0);

#define _DUSK_INTERNAL_ASSERT_WITH_MSG_(type, check, ...) _DUSK_INTERNAL_ASSERT_IMPL_(type, check, __VA_ARGS__)
#define _DUSK_INTERNAL_ASSERT_WITHOUT_MSG_(type, check) _DUSK_INTERNAL_ASSERT_IMPL_(type, check, "")

#define _DUSK_INTERNAL_ASSERT_GET_MACRO_NAME_(arg1, arg2, macro, ...) macro
// If there are two args in __VA_ARGS__, then the second parameter is the message, then we need `WITH_MSG` macro.
// If there is only one arg in __VA_ARGS__, then we need `WITHOUT_MSG` macro.
#define _DUSK_INTERNAL_ASSERT_GET_MACRO_(...) DUSK_EXPAND_MACRO(_DUSK_INTERNAL_ASSERT_GET_MACRO_NAME_(__VA_ARGS__, _DUSK_INTERNAL_ASSERT_WITH_MSG_, _DUSK_INTERNAL_ASSERT_WITHOUT_MSG_))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define DUSK_ASSERT(...) DUSK_EXPAND_MACRO(_DUSK_INTERNAL_ASSERT_GET_MACRO_(__VA_ARGS__)(_CLIENT_, __VA_ARGS__))
#define DUSK_CORE_ASSERT(...) DUSK_EXPAND_MACRO(_DUSK_INTERNAL_ASSERT_GET_MACRO_(__VA_ARGS__)(_CORE_, __VA_ARGS__))

#endif // !_DUSK_ASSERT_HPP_
