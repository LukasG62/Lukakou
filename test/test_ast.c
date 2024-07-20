#include "ast.h"

int main(int argc, char *argv[]) {
    DEBUG_PRINT("AST test\n");

    // Create the AST
    char varA[] = "a";
    char varB[] = "b";
    char varC[] = "c";
    char const1[] = "1";
    char const2[] = "2";
    char const3[] = "0";

    ast_node_t  *varADeclaration = create_ast_var_declaration_node(varA, TYPE_INT, create_ast_literal_node(const1));
    ast_node_t  *varBDeclaration = create_ast_var_declaration_node(varB, TYPE_INT, create_ast_literal_node(const2));
    ast_node_t  *varCDeclaration = create_ast_var_declaration_node(varC, TYPE_INT, create_ast_operator_node(OP_ADD, create_ast_variable_node(varA), create_ast_variable_node(varB)));
    ast_node_t  *ifCondition = create_ast_operator_node(OP_GT, create_ast_variable_node(varC), create_ast_literal_node(const2));
    ast_node_t  *ifBody = create_ast_return_node(create_ast_variable_node(varC));
    ast_node_t  *elseBody = create_ast_return_node(create_ast_literal_node(const3));
    ast_node_t  *ifElse = create_ast_if_node(ifCondition, ifBody, elseBody);
    ast_node_t  *startBody = create_ast_block_node();

    append_ast_node(startBody, varADeclaration);
    append_ast_node(startBody, varBDeclaration);
    append_ast_node(startBody, varCDeclaration);
    append_ast_node(startBody, ifElse);

    ast_node_t  *startFunction = create_ast_function_node("start", TYPE_INT, startBody);
    ast_node_t *program = create_ast_block_node();
    append_ast_node(program, startFunction);

    // Print the AST
    FILE *file = fopen("ast.dot", "w");
    gviz_ast_node(program, file);
    fclose(file);

    // Autre programme

    // Create the AST
    char varI[] = "i";
    char varSum[] = "sum";
    char const0[] = "0";
    char const10[] = "10";

    ast_node_t  *varIDeclaration = create_ast_operator_node(OP_ASSIGN, create_ast_variable_node(varI), create_ast_literal_node(const0));
    ast_node_t  *varSumDeclaration = create_ast_operator_node(OP_ASSIGN, create_ast_variable_node(varSum), create_ast_literal_node(const0));
    ast_node_t  *whileCondition = create_ast_operator_node(OP_LT, create_ast_variable_node(varI), create_ast_literal_node(const10));
    ast_node_t  *whileBody = create_ast_block_node();
    append_ast_node(whileBody, create_ast_operator_node(OP_ASSIGN, create_ast_variable_node(varSum), create_ast_operator_node(OP_ADD, create_ast_variable_node(varSum), create_ast_variable_node(varI))));
    append_ast_node(whileBody, create_ast_operator_node(OP_ASSIGN, create_ast_variable_node(varI), create_ast_operator_node(OP_ADD, create_ast_variable_node(varI), create_ast_literal_node(const1))));
    ast_node_t  *startBody2 = create_ast_block_node();
    append_ast_node(startBody2, varIDeclaration);
    append_ast_node(startBody2, varSumDeclaration);
    append_ast_node(startBody2, create_ast_while_node(whileCondition, whileBody));
    append_ast_node(startBody2, create_ast_return_node(create_ast_variable_node(varSum)));

    ast_node_t  *startFunction2 = create_ast_function_node("start", TYPE_INT, startBody2);
    ast_node_t *program2 = create_ast_block_node();
    append_ast_node(program2, startFunction2);

    // Print the AST
    FILE *file2 = fopen("ast2.dot", "w");
    gviz_ast_node(program2, file2);
    fclose(file2);

    // Free the AST
    free_ast_node(program);
    free_ast_node(program2);
    
    // run graphviz to generate the AST image
    system("dot -Tpng ast.dot -o ast.png");
    system("dot -Tpng ast2.dot -o ast2.png");

    return EXIT_SUCCESS;
}