/**
 * @file ast.h
 * @brief Abstract Syntax Tree header file
 * This file define the structure of the Abstract Syntax Tree.
 */

#ifndef AST_H
#define AST_H

#include "common.h"

// Graphviz constants

#define GVIZ_INTERNAL_NODE_STYLE "shape=box, style=filled, fillcolor=lightblue"
#define GVIZ_LEAF_NODE_STYLE "shape=ellipse, style=filled, fillcolor=lightgreen"
#define GVIZ_EDGE_STYLE "color=black"
#define GVIZ_FILE_HEADER "digraph G {\n"
#define GVIZ_FILE_FOOTER "}\n"
// Using the memory address of the node as the node name to get unique node names
#define GVIZ_ADD_EDGE(file, from, to) fprintf(file, "\"%p\" -> \"%p\" [%s];\n", from, to, GVIZ_EDGE_STYLE)
#define GVIZ_ADD_EDGE_TEXT(file, from, to, text) fprintf(file, "\"%p\" -> \"%p\" [%s, label=\"%s\"];\n", from, to, GVIZ_EDGE_STYLE, text)
#define GVIZ_ADD_NODE(file, node, style) fprintf(file, "\"%p\" [%s];\n", node, style)
#define GVIZ_ADD_NODE_TEXT(file, node, style, text) fprintf(file, "\"%p\" [%s, label=\"%s\"];\n", node, style, text)

/**
 * @enum ast_node_type_t
 * @brief AST node type enumeration
 * This is all the different "operations" that the Lukakou language can do.
 */
typedef enum {
    AST_NODE_BLOCK = 0, /*!< Block node */
    // Functions
    AST_NODE_FUNCTION, /*!< Function node */
    AST_NODE_FUNCTION_CALL, /*!< Function call node */
    AST_NODE_RETURN, /*!< Return node */

    // Iteration
    AST_NODE_FOR, /*!< For node */
    AST_NODE_WHILE, /*!< While node */
    AST_NODE_DO_WHILE, /*!< Do while node */
    AST_NODE_FOREACH, /*!< Foreach node */

    // Conditional (for now only if because i don't think we need else or elif (part of if node)
    AST_NODE_IF, /*!< If node */
    AST_NODE_IFNT, /*!< If not node */

    // Misc (idk how to implement them yet)
    AST_NODE_SYSTEM_INTERFACES, /*!< System interfaces node (System.io, System.syscall, etc) */
    AST_NODE_SYSTEM_SUBINTERFACE,

    // Variables (leaves of the tree)
    AST_NODE_LEAVES, /*!< Leaves of the tree */
    AST_NODE_VARIABLE, /*!< Variable node */
    AST_NODE_ARRAY, /*!< Array node */
    AST_NODE_STRING, /*!< String node */
    AST_NODE_CONSTANT, /*!< Constant node */
    AST_NODE_OPERATOR, /*!< Operator node */

} ast_node_type_t;

/**
 * @enum op_type_t
 * @brief Operation type enumeration
 * This is all the type of opérator for the AST_NODE_OPERATOR node.
 */
typedef enum {
    OP_ADD, /*!< Addition operator */
    OP_SUB, /*!< Substraction operator */
    OP_MUL, /*!< Multiplication operator */
    OP_DIV, /*!< Division operator */
    OP_MOD, /*!< Modulo operator */
    OP_AND, /*!< And operator */
    OP_OR, /*!< Or operator */
    OP_NOT, /*!< Not operator */
    OP_EQ, /*!< Equal operator */
    OP_NEQ, /*!< Not equal operator */
    OP_GT, /*!< Greater than operator */
    OP_LT, /*!< Less than operator */
    OP_GTE, /*!< Greater than or equal operator */
    OP_LTE, /*!< Less than or equal operator */
    OP_ASSIGN, /*!< Assign operator */
} op_type_t;

/**
 * @struct ast_node_block_t
 * @brief Block node structure
 * A block node is a node that contains a list of nodes. This is used for functions, loops, if bodies and the main block.
 * The block node is the root node of the AST.
 */
typedef struct {
    struct __ast_node_t **nodes; /*!< List of nodes */
    size_t nodesLen; /*!< Number of nodes */
} ast_node_block_t;

/**
 * @struct ast_node_function_t
 * @brief Function node structure
 * A function node is a node that contains the function name, the arguments and the body.
 */
typedef struct {
    char *name; /*!< Function name */
    struct __ast_node_t **args; /*!< List of arguments */
    size_t argsLen; /*!< Number of arguments */
    struct __ast_node_t *body; /*!< Function body */
} ast_node_function_t;

/**
 * @struct ast_node_function_call_t
 * @brief Function call node structure
 * A function call node is a node that contains the function name and the arguments.
 */
typedef struct {
    char *name; /*!< Function name */
    struct __ast_node_t **args; /*!< List of arguments */
    size_t argsLen; /*!< Number of arguments */
} ast_node_function_call_t;

/**
 * @struct ast_node_return_t
 * @brief Return node structure
 * A return node is a node that contains the return value.
 */
typedef struct {
    struct __ast_node_t *value; /*!< Return value */
} ast_node_return_t;

/**
 * @struct ast_node_for_t
 * @brief For node structure
 * A for node is a node that contains the initialization, the condition, the increment and the body.
 */
typedef struct {
    struct __ast_node_t *init; /*!< Initialization */
    struct __ast_node_t *condition; /*!< Condition */
    struct __ast_node_t *increment; /*!< Increment */
    struct __ast_node_t *body; /*!< Body */
} ast_node_for_t;

/**
 * @struct ast_node_while_t
 * @brief While node structure
 * A while node is a node that contains the condition and the body.
 */
typedef struct {
    struct __ast_node_t *condition; /*!< Condition */
    struct __ast_node_t *body; /*!< Body */
} ast_node_while_t;

/**
 * @struct ast_node_do_while_t
 * @brief Do while node structure
 * A do while node is a node that contains the condition and the body.
 */
typedef ast_node_while_t ast_node_do_while_t; // dowhile is the same as while

/**
 * @struct ast_node_foreach_t
 * @brief Foreach node structure
 * A foreach node is a node that contains the variable, the array and the body.
 */
typedef struct {
    struct __ast_node_t *variable; /*!< Variable */
    struct __ast_node_t *array; /*!< Array */
    struct __ast_node_t *body; /*!< Body */
} ast_node_foreach_t;

/**
 * @struct ast_node_if_t
 * @brief If node structure
 * A if node is a node that contains the condition and the body.
 */
typedef struct {
    struct __ast_node_t *condition; /*!< Condition */
    struct __ast_node_t *trueBranch; /*!< True branch */
    struct __ast_node_t *falseBranch; /*!< False branch */
} ast_node_if_t;

/**
 * @struct ast_node_variable_t
 * @brief Variable node structure
 * A variable node is a node that contains the variable name.
 */
typedef struct {
    char *name; /*!< Variable name */
} ast_node_variable_t;

/**
 * @struct ast_node_array_t
 * @brief Array node structure
 * A array node is a node that contains the array name and the index.
 */
typedef struct {
    char *name; /*!< Array name */
    struct __ast_node_t *arrayIndex; /*!< Array index */
} ast_node_array_t;

typedef struct {
    char *value; /*!< Constant value */
} ast_node_constant_t; /*!< Constant node is the same as variable node */

typedef ast_node_constant_t ast_node_string_t; /*!< String node is the same as constant node */

/**
 * @struct ast_node_operator_t
 * @brief Operator node structure
 * A operator node is a node that contains the left and right operands and the operator type.
 */
typedef struct {
    op_type_t type; /*!< Operator type */
    struct __ast_node_t *left; /*!< Left operand */
    struct __ast_node_t *right; /*!< Right operand */
} ast_node_operator_t;

typedef struct __ast_node_t {
    // we need to know the parent node to be able to perform in-order traversal of the tree
    // like this we can make a functino call next_ast_node(node) that will return the next node in the tree
    struct __ast_node_t *parent; /*!< Parent node (NULL if root node) */
    ast_node_type_t type; /*!< Node type */
    void *data;
    
    // all possible data for a node    
    union {
        ast_node_block_t block; /*!< Block node */
        ast_node_function_t function; /*!< Function node */
        ast_node_function_call_t functionCall; /*!< Function call node */
        ast_node_return_t returnNode; /*!< Return node */
        ast_node_for_t forNode; /*!< For node */
        ast_node_while_t whileNode; /*!< While node */
        ast_node_do_while_t doWhileNode; /*!< Do while node */
        ast_node_foreach_t foreachNode; /*!< Foreach node */
        ast_node_if_t ifNode; /*!< If node */
        ast_node_variable_t variable; /*!< Variable node */
        ast_node_array_t array; /*!< Array node */
        ast_node_string_t string; /*!< String node */
        ast_node_constant_t constant; /*!< Constant node */
        ast_node_operator_t operator; /*!< Operator node */
    } _udata;
} ast_node_t;

/**
 * @struct ast_stack_t
 * @brief A stack of AST nodes used to keep track of the nodes that have been visited
 */
typedef struct __ast_stack_t {
    ast_node_t *node; /*!< AST node */
    struct __ast_stack_t *next; /*!< Next node in the stack */
} ast_stack_t;

/**
 * @fn ast_node_t *create_ast_node(ast_node_type_t type)
 * @brief Create a new AST node
 * @param type Node type
 * @return A new AST node
 */
ast_node_t *create_ast_node(ast_node_type_t type);

/**
 * @fn ast_node_t *create_ast_operator_node(op_type_t type, ast_node_t *left, ast_node_t *right)
 * @brief Create a new AST operator node
 * @param type Operator type
 * @param left Left operand
 * @param right Right operand
 * @return A new AST operator node
*/
ast_node_t *create_ast_operator_node(op_type_t type, ast_node_t *left, ast_node_t *right);

/**
 * @fn ast_node_t *create_ast_variable_node(char *name);
 * @brief Create a new AST variable node
 * @param name Variable name
 * @return A new AST variable node
 */
ast_node_t *create_ast_variable_node(char *name);

/**
 * @fn ast_node_t *create_ast_array_node(char *name, ast_node_t *index)
 * @brief Create a new AST array node
 * @param name Array name
 * @param index Array index
 * @return A new AST array node
 */ 
ast_node_t *create_ast_array_node(char *name, ast_node_t *index);

/**
 * @fn ast_node_t *create_ast_string_node(char *value)
 * @brief Create a new AST string node
 * @param value String value
 * @return A new AST string node
 */
ast_node_t *create_ast_string_node(char *value);

/**
 * @fn ast_node_t *create_ast_constant_node(char *value)
 * @brief Create a new AST constant node
 * @param value Constant value
 * @return A new AST constant node
 */
ast_node_t *create_ast_constant_node(char *value);

/**
 * @fn ast_node_t *create_ast_block_node(ast_node_t **nodes, size_t nodesLen)
 * @brief Create a new AST block node
 * @return A new AST block node
 */
ast_node_t *create_ast_block_node(ast_node_t **nodes, size_t nodesLen);

/**
 * @fn ast_node_t *create_ast_function_node(char *name, ast_node_t **args, size_t argsLen, ast_node_t *body)
 * @brief Create a new AST function node
 * @param name Function name
 * @param args Function arguments
 * @param argsLen Number of arguments
 * @param body Function body
 * @return A new AST function node
 */
ast_node_t *create_ast_function_node(char *name, ast_node_t **args, size_t argsLen, ast_node_t *body);

/**
 * @fn ast_node_t *create_ast_function_call_node(char *name, ast_node_t **args, size_t argsLen)
 * @brief Create a new AST function call node
 * @param name Function name
 * @param args Function arguments
 * @param argsLen Number of arguments
 * @return A new AST function call node
 */
ast_node_t *create_ast_function_call_node(char *name, ast_node_t **args, size_t argsLen);

/**
 * @fn ast_node_t *create_ast_return_node(ast_node_t *value)
 * @brief Create a new AST return node
 * @param value Return value
 * @return A new AST return node
 */
ast_node_t *create_ast_return_node(ast_node_t *value);

/**
 * @fn ast_node_t *create_ast_for_node(ast_node_t *init, ast_node_t *condition, ast_node_t *increment, ast_node_t *body)
 * @brief Create a new AST for node
 * @param init Initialization
 * @param condition Condition
 * @param increment Increment
 * @param body Body
 * @return A new AST for node
 */
ast_node_t *create_ast_for_node(ast_node_t *init, ast_node_t *condition, ast_node_t *increment, ast_node_t *body);

/**
 * @fn ast_node_t *create_ast_while_node(ast_node_t *condition, ast_node_t *body)
 * @brief Create a new AST while node
 * @param condition Condition
 * @param body Body
 * @return A new AST while node
 */
ast_node_t *create_ast_while_node(ast_node_t *condition, ast_node_t *body);

/**
 * @fn ast_node_t *create_ast_do_while_node(ast_node_t *condition, ast_node_t *body)
 * @brief Create a new AST do while node
 * @param condition Condition
 * @param body Body
 * @return A new AST do while node
 */
ast_node_t *create_ast_do_while_node(ast_node_t *condition, ast_node_t *body);

/**
 * @fn ast_node_t *create_ast_foreach_node(ast_node_t *variable, ast_node_t *array, ast_node_t *body)
 * @brief Create a new AST foreach node
 * @param variable Variable
 * @param array Array
 * @param body Body
 * @return A new AST foreach node
 */
ast_node_t *create_ast_foreach_node(ast_node_t *variable, ast_node_t *array, ast_node_t *body);

/**
 * @fn ast_node_t *create_ast_if_node(ast_node_t *condition, ast_node_t *trueBranch, ast_node_t *falseBranch)
 * @brief Create a new AST if node
 * @param condition Condition
 * @param trueBranch True branch
 * @param falseBranch False branch
 * @return A new AST if node
 */
ast_node_t *create_ast_if_node(ast_node_t *condition, ast_node_t *trueBranch, ast_node_t *falseBranch);


/**
 * @fn void free_ast_node(ast_node_t *node)
 * @brief Free an AST node
 * @param node AST node
 * @return void
 */
void free_ast_node(ast_node_t *node);

/**
 * @fn const char *str_ast_node_type(ast_node_type_t type)
 * @brief Get the string representation of an AST node type
 * @param type AST node type
 * @return The string representation
 */
const char *str_ast_node_type(ast_node_type_t type);

/**
 * @fn const char *str_op_type(op_type_t type)
 * @brief Get the string representation of an operation type
 * @param type Operation type
 * @return The string representation
 */
const char *str_op_type(op_type_t type);

/**
 * @fn void append_ast_node(ast_node_t *parent, ast_node_t *child)
 * @brief Append a child node to a parent node
 * @param parent Parent node
 * @param child Child node
*/
void append_ast_node(ast_node_t *parent, ast_node_t *child);

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
ast_node_t *next_ast_node(ast_node_t *node, ast_stack_t **stack);

/**
 * @fn void free_ast_stack(ast_stack_t *stack)
 * @brief Free an AST stack
 * @param stack AST stack
 * @return void
 */
void free_ast_stack(ast_stack_t *stack);

/**
 * @fn add_to_ast_stack(ast_stack_t **stack, ast_node_t *node)
 * @brief Add a node to the AST stack
 * @param stack AST stack
 * @param node AST node
 * @return void
 */
void add_to_ast_stack(ast_stack_t **stack, ast_node_t *node);

/**
 * @fn ast_node_t *pop_ast_stack(ast_stack_t **stack)
 * @brief Pop a node from the AST stack
 * @param stack AST stack
 * @return The popped node
 */
ast_node_t *pop_ast_stack(ast_stack_t **stack);

/**
 * @fn gviz_ast_node(ast_node_t *node, FILE *file)
 * @brief Generate a Graphviz file from an AST node
 * @param node AST node
 * @param file File
 * @return void
 */
void gviz_ast_node(ast_node_t *node, FILE *file);



#endif // AST_H