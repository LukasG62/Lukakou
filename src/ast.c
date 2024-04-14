/**
 * @file ast.c
 * @brief Abstract Syntax Tree (AST) implementation
*/
#include "ast.h"

/**********************************************************************************************************************/
/*                                           Private functions signatures                                             */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/*                                           Public functions definitions                                             */
/**********************************************************************************************************************/

/**
 * @fn ast_node_t *create_ast_node(ast_node_type_t type)
 * @brief Create a new AST node
 * @param type Node type
 * @return A new AST node
 */
ast_node_t *create_ast_node(ast_node_type_t type) {
    UNIMPLEMENTED("create_ast_node");
}

/**
 * @fn void free_ast_node(ast_node_t *node)
 * @brief Free an AST node
 * @param node AST node
 * @return void
 */
void free_ast_node(ast_node_t *node) {
    UNIMPLEMENTED("free_ast_node");

}

/**
 * @fn const char *str_ast_node_type(ast_node_type_t type)
 * @brief Get the string representation of an AST node type
 * @param type AST node type
 * @return The string representation
 */
const char *str_ast_node_type(ast_node_type_t type) {
    UNIMPLEMENTED("str_ast_node_type");
}

/**
 * @fn const char *str_op_type(op_type_t type)
 * @brief Get the string representation of an operation type
 * @param type Operation type
 * @return The string representation
 */
const char *str_op_type(op_type_t type) {
    UNIMPLEMENTED("str_op_type");

}

/**
 * @fn void append_ast_node(ast_node_t *parent, ast_node_t *child)
 * @brief Append a child node to a parent node
 * @param parent Parent node
 * @param child Child node
*/
void append_ast_node(ast_node_t *parent, ast_node_t *child) {
    UNIMPLEMENTED("append_ast_node");
}

/**
 * @fn ast_node_t *next_ast_node(ast_node_t *node, ast_stack_t **stack)
 * @brief Get the next node in the AST tree
 * @param node Current node
 * @param stack Stack of nodes
 * @return The next node
 * @note When the function is called for the first time, the stack must be NULL.
 * The stack is used to keep track of the nodes that have been visited.
 * @note this function return NULL when there is no more node to visit
 * if so, the stack is freed and set to NULL automatically.
 * @warning the stack must not be modified by external functions or the behavior is undefined.
 */
ast_node_t *next_ast_node(ast_node_t *node, ast_stack_t **stack) {
    UNIMPLEMENTED("next_ast_node");
}

/**
 * @fn void free_ast_stack(ast_stack_t *stack)
 * @brief Free an AST stack
 * @param stack AST stack
 * @return void
 */
void free_ast_stack(ast_stack_t *stack) {
    UNIMPLEMENTED("free_ast_stack");
}

/**
 * @fn add_to_ast_stack(ast_stack_t **stack, ast_node_t *node)
 * @brief Add a node to the AST stack
 * @param stack AST stack
 * @param node AST node
 * @return void
 */
void add_to_ast_stack(ast_stack_t **stack, ast_node_t *node) {
    UNIMPLEMENTED("add_to_ast_stack");
}

/**
 * @fn ast_node_t *pop_ast_stack(ast_stack_t **stack)
 * @brief Pop a node from the AST stack
 * @param stack AST stack
 * @return The popped node
 */
ast_node_t *pop_ast_stack(ast_stack_t **stack) {
    UNIMPLEMENTED("pop_ast_stack");
}

/**
 * @fn gviz_ast_node(ast_node_t *node, FILE *file)
 * @brief Generate a Graphviz file from an AST node
 * @param node AST node
 * @param file File
 * @return void
 */
void gviz_ast_node(ast_node_t *node, FILE *file) {
    UNIMPLEMENTED("gviz_ast_node");
}