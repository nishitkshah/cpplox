import sys

# TODO: Fix this code based on latest changes in AST Class definition format

class ClassDefinition:
    def __init__(self, class_name, field_list):
        class_name = class_name.strip()
        field_list = field_list.strip()
        self.class_name = class_name
        self.field_list = field_list
        self.fields = field_list.split(", ")
        self.field_types = [field.split()[0] for field in self.fields]
        self.field_names = [field.split()[1] for field in self.fields]

def add_to_file(file_obj, indent, line, newline=True):
    indent_text = "    " * indent
    line = indent_text + line
    if newline:
        line = line + '\n'
    file_obj.write(line)

def generate_visitor_class(file_obj, base_name, subclasses, indent):
    add_to_file(file_obj, indent, "")
    add_to_file(file_obj, indent, "template <class T>")
    add_to_file(file_obj, indent, "class %s::Visitor {" % base_name)
    for subclass in subclasses:
        add_to_file(file_obj, indent+1, "virtual T visit%s%s(%s* %s)=0;" % (
            subclass.class_name,
            base_name,
            subclass.class_name,
            base_name.lower()
        ))
    add_to_file(file_obj, indent, "};    // class Visitor")

def generate_subclasses(file_obj, base_name, subclasses, indent):
    for subclass in subclasses:
        add_to_file(file_obj, indent, "")
        add_to_file(file_obj, indent, "class %s::%s : public %s {" % (
            base_name,
            subclass.class_name,
            base_name,
        ))
        add_to_file(file_obj, indent+1, "public:")
        add_to_file(file_obj, indent+2, "%s(%s);" % (
            subclass.class_name,
            subclass.field_list,
        ))
        add_to_file(file_obj, indent+2, "")
        add_to_file(file_obj, indent+2, "template <class T>")
        add_to_file(file_obj, indent+2, "T accept(%s::Visitor<T> &visitor);" % base_name)
        add_to_file(file_obj, indent+2, "")
        for field in subclass.fields:
            add_to_file(file_obj, indent+2, "%s;" % field)
        add_to_file(file_obj, indent, "};    // class %s" % subclass.class_name)

def generate_base_class(file_obj, base_name, subclasses, indent):
    add_to_file(file_obj, indent, "")
    add_to_file(file_obj, indent, "class %s {" % base_name)
    add_to_file(file_obj, indent+1, "// Abstract class for Abstract Syntax Tree")
    add_to_file(file_obj, indent+1, "public:")
    for subclass in subclasses:
        add_to_file(file_obj, indent+2, "class %s;" % subclass.class_name)
    add_to_file(file_obj, indent+2, "template <class T>")
    add_to_file(file_obj, indent+2, "class Visitor;")
    add_to_file(file_obj, indent+2, "")
    add_to_file(file_obj, indent+2, "template <class T>")
    add_to_file(file_obj, indent+2, "T accept(Visitor<T> &visitor){}")
    add_to_file(file_obj, indent, "};    // class %s" % base_name)

def generate_subclass_definition(file_obj, base_name, subclasses, indent):
    for subclass in subclasses:
        add_to_file(file_obj, indent, "")
        add_to_file(file_obj, indent, "%s::%s::%s(%s) :" % (
            base_name,
            subclass.class_name,
            subclass.class_name,
            subclass.field_list,
        ))
        cnt = 1
        for field_name in subclass.field_names:
            if cnt != len(subclass.field_names):
                add_to_file(file_obj, indent+1, "%s(%s)," % (
                    field_name,
                    field_name,
                ))
            else:
                add_to_file(file_obj, indent+1, "%s(%s)" % (
                    field_name,
                    field_name,
                ))
            cnt += 1
        add_to_file(file_obj, indent, "{}")
        add_to_file(file_obj, indent, "")
        add_to_file(file_obj, indent, "template <class T>")
        add_to_file(file_obj, indent, "T %s::%s::accept(Visitor<T> &visitor) {" % (
            base_name,
            subclass.class_name,
        ))
        add_to_file(file_obj, indent+1, "return visitor.visit%s%s(this);" % (
            subclass.class_name,
            base_name,
        ))
        add_to_file(file_obj, indent, "}")

def generate_header_file(file_obj, base_name, subclasses, indent=0):
    add_to_file(file_obj, indent, "// Reference: http://www.craftinginterpreters.com/")
    add_to_file(file_obj, indent, "")
    add_to_file(file_obj, indent, "#ifndef EXPR_H")
    add_to_file(file_obj, indent, "#define EXPR_H")
    add_to_file(file_obj, indent, "")
    add_to_file(file_obj, indent, "#include <string>")
    add_to_file(file_obj, indent, "#include \"token.hpp\"")
    add_to_file(file_obj, indent, "")
    add_to_file(file_obj, indent, "namespace lox {")
    generate_base_class(file_obj, base_name, subclasses, indent+1)
    generate_visitor_class(file_obj, base_name, subclasses, indent+1)
    generate_subclasses(file_obj, base_name, subclasses, indent+1)
    add_to_file(file_obj, indent+1, "")
    add_to_file(file_obj, indent, "} // namespace lox")
    add_to_file(file_obj, indent, "")
    add_to_file(file_obj, indent, "#endif")

def generate_definition_file(file_obj, base_name, subclasses, indent=0):
    add_to_file(file_obj, indent, "// Reference: http://www.craftinginterpreters.com/")
    add_to_file(file_obj, indent, "")
    add_to_file(file_obj, indent, "#include \"expr.hpp\"")
    add_to_file(file_obj, indent, "#include <string>")
    add_to_file(file_obj, indent, "#include \"token.hpp\"")
    add_to_file(file_obj, indent, "")
    add_to_file(file_obj, indent, "namespace lox {")
    generate_subclass_definition(file_obj, base_name, subclasses, indent+1)
    add_to_file(file_obj, indent+1, "")
    add_to_file(file_obj, indent, "} // namespace lox")

def define_ast(output_dir, base_name, types):
    subclasses = [ClassDefinition(*(type.split(':', 1))) for type in types]
    header_path = output_dir + "/" + base_name.lower() + ".hpp"
    with open(header_path, "w+") as ast_header_file:
        generate_header_file(
            file_obj=ast_header_file,
            base_name=base_name,
            subclasses=subclasses,
            indent=0,
        )
    definition_path = output_dir + "/" + base_name.lower() + ".cpp"
    with open(definition_path, "w+") as ast_definition_file:
        generate_definition_file(
            file_obj=ast_definition_file,
            base_name=base_name,
            subclasses=subclasses,
            indent=0,
        )

if len(sys.argv)!=2:
    print("Usage: generate_ast <output directory>")
    sys.exit(0)
output_dir = sys.argv[1]
define_ast(output_dir, "Expr", [
    "Binary   : Expr* left, Token oper, Expr* right",
    "Grouping : Expr* expression",
    "Literal  : std::string value",
    "Unary    : Token oper, Expr* right",
])
