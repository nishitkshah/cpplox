// Reference: http://www.craftinginterpreters.com/

#include "visitor_return.hpp"

namespace lox {

    VisitorReturn::VisitorReturn(VisitorReturnType return_type, void* return_pointer) :
        return_type(return_type),
        return_pointer(return_pointer)
    {}

} // namespace lox
