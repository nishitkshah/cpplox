import sys

def get_visitor_class(base_name, types):
    visitor_class = "template <class T>\n"
    visitor_class += "class Visitor {\n"
    for subclass in types:
        class_name = subclass.split(':', 1)[0].strip()
        visitor_class += "    virtual T visit" + class_name + base_name + "(" + \
            class_name + " " + base_name.lower() + ")=0;\n"
    visitor_class += "};    // class Visitor\n"
    return visitor_class

def define_type(base_name, class_name, fields):
    type_definition = "class " + class_name + " : public " + base_name + " {\n"
    type_definition += "    public:\n"
    type_definition += "        " + class_name + "(" + fields + ") {\n"
    for field in fields.split(", "):
        field_name = field.split()[1]
        type_definition += "            this->" + field_name + " = " + field_name + ";\n"
    type_definition += "        }\n"
    type_definition += "        \n"
    type_definition += "        template <class T>\n"
    type_definition += "        T accept(Visitor<T> visitor) {\n"
    type_definition += "            return visitor.visit" + class_name + base_name + "(*this);\n"
    type_definition += "        }\n"
    type_definition += "        \n"
    for field in fields.split(", "):
        type_definition += "        " + field + ";\n"
    type_definition += "};    // class " + class_name + "\n"
    return type_definition

def get_subclass_content(base_name, types):
    subclass_content = '\n'
    for subclass in types:
        class_name = subclass.split(':', 1)[0].strip()
        fields = subclass.split(':', 1)[1].strip()
        subclass_content += define_type(base_name, class_name, fields)
        subclass_content += '\n'
    return subclass_content

def generate_base_class(ast_file, base_name, visitor_class, subclass_content):
    ast_file.write("// Reference: http://www.craftinginterpreters.com/\n")
    ast_file.write("\n")
    ast_file.write("#ifndef " + base_name.upper() + "_H\n")
    ast_file.write("#define " + base_name.upper() + "_H\n")
    ast_file.write("\n")
    ast_file.write("#include <string>\n")
    ast_file.write("#include \"token.hpp\"\n")
    ast_file.write("\n")
    ast_file.write("namespace lox {\n")
    ast_file.write("\n")
    ast_file.write("    class " + base_name + " {\n")
    ast_file.write("        // Abstract class for Abstract Syntax Tree\n")
    ast_file.write("        public:\n")
    visitor_class = visitor_class.split('\n')
    for line in visitor_class:
        ast_file.write("            " + line + "\n")
    ast_file.write("        template <class T>\n")
    ast_file.write("        T accept(Visitor<T> visitor){}\n")
    ast_file.write("    };    // class " + base_name + "\n")
    subclass_content = subclass_content.split('\n')
    for line in subclass_content:
        ast_file.write("    " + line + "\n")
    ast_file.write("} // namespace lox\n")
    ast_file.write("\n")
    ast_file.write("#endif\n")

def define_ast(output_dir, base_name, types):
    path = output_dir + "/" + base_name.lower() + ".hpp"
    with open(path, "w+") as ast_file:
        generate_base_class(ast_file, base_name,
            get_visitor_class(base_name, types),
            get_subclass_content(base_name, types),
        )

if len(sys.argv)!=2:
    print("Usage: generate_ast <output directory>")
output_dir = sys.argv[1]
define_ast(output_dir, "Expr", [
    "Binary   : Expr left, Token oper, Expr right",
    "Grouping : Expr expression",
    "Literal  : std::string value",
    "Unary    : Token oper, Expr right",
])
