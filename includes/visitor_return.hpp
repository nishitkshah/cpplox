// Reference: http://www.craftinginterpreters.com/

#ifndef VISITOR_RETURN_H
#define VISITOR_RETURN_H

namespace lox {

    enum class VisitorReturnType {
        STRING, VOID
    };

    class VisitorReturn {
        public:
            VisitorReturnType return_type;
            void* return_pointer;

            VisitorReturn(VisitorReturnType return_type, void* return_pointer);
    };

} // namespace lox

#endif
