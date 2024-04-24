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
    // Allocate memory for the new node
    ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));
    CHECK_ALLOC(node, "create_ast_node: node");
    // Initialize the node
    node->type = type;
    node->parent = NULL; // by default is a orphan node
    return node;
}

/**
 * @fn ast_node_t *create_ast_operator_node(op_type_t type, ast_node_t *left, ast_node_t *right)
 * @brief Create a new AST operator node
 * @param type Operator type
 * @param left Left operand
 * @param right Right operand
 * @return A new AST operator node
*/
ast_node_t *create_ast_operator_node(op_type_t type, ast_node_t *left, ast_node_t *right) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_OPERATOR);
    // Initialize the node
    node->_udata.operator.type = type;
    node->_udata.operator.left = left;
    node->_udata.operator.right = right;
    node->data = &node->_udata.operator;
    return node;
}

/**
 * @fn ast_node_t *create_ast_variable_node(char *name);
 * @brief Create a new AST variable node
 * @param name Variable name
 * @return A new AST variable node
 */
ast_node_t *create_ast_variable_node(char *name) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_VARIABLE);
    // Initialize the node
    node->_udata.variable.name = name;
    node->data = &node->_udata.variable;
    return node;
}

/**
 * @fn ast_node_t *create_ast_array_node(char *name, ast_node_t *index)
 * @brief Create a new AST array node
 * @param name Array name
 * @param index Array index
 * @return A new AST array node
 */ 
ast_node_t *create_ast_array_node(char *name, ast_node_t *index) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_ARRAY);
    // Initialize the node
    node->_udata.array.name = name;
    node->_udata.array.arrayIndex = index;
    node->data = &node->_udata.array;
    return node;
}

/**
 * @fn ast_node_t *create_ast_string_node(char *value)
 * @brief Create a new AST string node
 * @param value String value
 * @return A new AST string node
 */
ast_node_t *create_ast_string_node(char *value) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_STRING);
    // Initialize the node
    node->_udata.string.value = value;
    node->data = &node->_udata.string;
    return node;
}
/**
 * @fn ast_node_t *create_ast_constant_node(char *value)
 * @brief Create a new AST constant node
 * @param value Constant value
 * @return A new AST constant node
 */
ast_node_t *create_ast_constant_node(char *value) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_CONSTANT);
    // Initialize the node
    node->_udata.constant.value = value;
    node->data = &node->_udata.constant;
    return node;
}
/**
 * @fn ast_node_t *create_ast_block_node(ast_node_t **nodes, size_t nodesLen)
 * @brief Create a new AST block node
 * @return A new AST block node
 */
ast_node_t *create_ast_block_node(ast_node_t **nodes, size_t nodesLen) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_BLOCK);
    // Initialize the node
    node->_udata.block.nodes = nodes;
    node->_udata.block.nodesLen = nodesLen;
    node->data = &node->_udata.block;
    return node;
}

/**
 * @fn ast_node_t *create_ast_function_node(char *name, ast_node_t **args, size_t argsLen, ast_node_t *body)
 * @brief Create a new AST function node
 * @param name Function name
 * @param args Function arguments
 * @param argsLen Number of arguments
 * @param body Function body
 * @return A new AST function node
 */
ast_node_t *create_ast_function_node(char *name, ast_node_t **args, size_t argsLen, ast_node_t *body) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_FUNCTION);
    // Initialize the node
    node->_udata.function.name = name;
    node->_udata.function.args = args;
    node->_udata.function.argsLen = argsLen;
    node->_udata.function.body = body;
    return node;
}

/**
 * @fn ast_node_t *create_ast_function_call_node(char *name, ast_node_t **args, size_t argsLen)
 * @brief Create a new AST function call node
 * @param name Function name
 * @param args Function arguments
 * @param argsLen Number of arguments
 * @return A new AST function call node
 */
ast_node_t *create_ast_function_call_node(char *name, ast_node_t **args, size_t argsLen) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_FUNCTION_CALL);
    // Initialize the node
    node->_udata.functionCall.name = name;
    node->_udata.functionCall.args = args;
    node->_udata.functionCall.argsLen = argsLen;
    node->data = &node->_udata.functionCall;
    return node;
}

/**
 * @fn ast_node_t *create_ast_return_node(ast_node_t *value)
 * @brief Create a new AST return node
 * @param value Return value
 * @return A new AST return node
 */
ast_node_t *create_ast_return_node(ast_node_t *value) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_RETURN);
    // Initialize the node
    node->_udata.returnNode.value = value;
    node->data = &node->_udata.returnNode;
    return node;
}
/**
 * @fn ast_node_t *create_ast_for_node(ast_node_t *init, ast_node_t *condition, ast_node_t *increment, ast_node_t *body)
 * @brief Create a new AST for node
 * @param init Initialization
 * @param condition Condition
 * @param increment Increment
 * @param body Body
 * @return A new AST for node
 */
ast_node_t *create_ast_for_node(ast_node_t *init, ast_node_t *condition, ast_node_t *increment, ast_node_t *body) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_FOR);
    // Initialize the node
    node->_udata.forNode.init = init;
    node->_udata.forNode.condition = condition;
    node->_udata.forNode.increment = increment;
    node->_udata.forNode.body = body;
    node->data = &node->_udata.forNode;
    return node;
}
/**
 * @fn ast_node_t *create_ast_while_node(ast_node_t *condition, ast_node_t *body)
 * @brief Create a new AST while node
 * @param condition Condition
 * @param body Body
 * @return A new AST while node
 */
ast_node_t *create_ast_while_node(ast_node_t *condition, ast_node_t *body) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_WHILE);
    // Initialize the node
    node->_udata.whileNode.condition = condition;
    node->_udata.whileNode.body = body;
    node->data = &node->_udata.whileNode;
    return node;
}

/**
 * @fn ast_node_t *create_ast_do_while_node(ast_node_t *condition, ast_node_t *body)
 * @brief Create a new AST do while node
 * @param condition Condition
 * @param body Body
 * @return A new AST do while node
 */
ast_node_t *create_ast_do_while_node(ast_node_t *condition, ast_node_t *body) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_DO_WHILE);
    // Initialize the node
    node->_udata.doWhileNode.condition = condition;
    node->_udata.doWhileNode.body = body;
    node->data = &node->_udata.doWhileNode;
    return node;
}

/**
 * @fn ast_node_t *create_ast_foreach_node(ast_node_t *variable, ast_node_t *array, ast_node_t *body)
 * @brief Create a new AST foreach node
 * @param variable Variable
 * @param array Array
 * @param body Body
 * @return A new AST foreach node
 */
ast_node_t *create_ast_foreach_node(ast_node_t *variable, ast_node_t *array, ast_node_t *body) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_FOREACH);
    // Initialize the node
    node->_udata.foreachNode.variable = variable;
    node->_udata.foreachNode.array = array;
    node->_udata.foreachNode.body = body;
    node->data = &node->_udata.foreachNode;
    return node;
}

/**
 * @fn ast_node_t *create_ast_if_node(ast_node_t *condition, ast_node_t *trueBranch, ast_node_t *falseBranch)
 * @brief Create a new AST if node
 * @param condition Condition
 * @param trueBranch True branch
 * @param falseBranch False branch
 * @return A new AST if node
 */
ast_node_t *create_ast_if_node(ast_node_t *condition, ast_node_t *trueBranch, ast_node_t *falseBranch) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_IF);
    // Initialize the node
    node->_udata.ifNode.condition = condition;
    node->_udata.ifNode.trueBranch = trueBranch;
    node->_udata.ifNode.falseBranch = falseBranch;
    node->data = &node->_udata.ifNode;
    return node;
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
    switch(type) {
        case AST_NODE_OPERATOR: return "OPERATOR";
        case AST_NODE_VARIABLE: return "VARIABLE";
        case AST_NODE_ARRAY: return "ARRAY";
        case AST_NODE_STRING: return "STRING";
        case AST_NODE_CONSTANT: return "CONSTANT";
        case AST_NODE_BLOCK: return "BLOCK";
        case AST_NODE_FUNCTION: return "FUNCTION";
        case AST_NODE_FUNCTION_CALL: return "FUNCTION CALL";
        case AST_NODE_RETURN: return "RETURN";
        case AST_NODE_FOR: return "FOR";
        case AST_NODE_WHILE: return "WHILE";
        case AST_NODE_DO_WHILE: return "DO WHILE";
        case AST_NODE_FOREACH: return "FOREACH";
        case AST_NODE_IF: return "IF";
        default: return "UKNOWN";
    }
}

/**
 * @fn const char *str_op_type(op_type_t type)
 * @brief Get the string representation of an operation type
 * @param type Operation type
 * @return The string representation
 */
const char *str_op_type(op_type_t type) {
    switch(type) {
        case OP_ADD: return "ADD";
        case OP_SUB: return "SUB";
        case OP_MUL: return "MUL";
        case OP_DIV: return "DIV";
        case OP_MOD: return "MOD";
        case OP_ASSIGN: return "ASSIGN";
        case OP_EQ: return "EQ";
        case OP_NEQ: return "NEQ";
        case OP_GT: return "GT";
        case OP_LT: return "LT";
        case OP_GTE: return "GTE";
        case OP_LTE: return "LTE";
        case OP_AND: return "AND";
        case OP_OR: return "OR";
        case OP_NOT: return "NOT";
        default: return "UNKNOWN";
    }

}

/**
 * @fn void append_ast_node(ast_node_t *parent, ast_node_t *child)
 * @brief Append a child node to a parent node
 * @param parent Parent node
 * @param child Child node
*/
void append_ast_node(ast_node_t *parent, ast_node_t *child) {
    child->parent = parent;
    // Check if the parent is a block node
    if(parent->type == AST_NODE_BLOCK) {
        // Resize the nodes array and append the child node
        ast_node_block_t *block = (ast_node_block_t *)parent->data;
        block->nodes = (ast_node_t **)realloc(block->nodes, sizeof(ast_node_t *) * (block->nodesLen + 1));
        CHECK_ALLOC(block->nodes, "append_ast_node: block->nodes");
        block->nodes[block->nodesLen++] = child;
        return;
    }
    // Can't append a child to a non block node
    else {
        ERROR("append_ast_node: parent node is not a block node");
    }
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
    return NULL;
}

/**
 * @fn void free_ast_stack(ast_stack_t *stack)
 * @brief Free an AST stack
 * @param stack AST stack
 * @return void
 */
void free_ast_stack(ast_stack_t *stack) {
    if(stack != NULL) {
        free_ast_stack(stack->next);
        free(stack);
        stack = NULL;
    }
}

/**
 * @fn add_to_ast_stack(ast_stack_t **stack, ast_node_t *node)
 * @brief Add a node to the AST stack
 * @param stack AST stack
 * @param node AST node
 * @return void
 */
void add_to_ast_stack(ast_stack_t **stack, ast_node_t *node) {
    if(stack == NULL) {
        ERROR("add_to_ast_stack: stack is NULL");
    }

    if(*stack == NULL) {
        *stack = (ast_stack_t *)malloc(sizeof(ast_stack_t));
        CHECK_ALLOC(*stack, "add_to_ast_stack: stack");
        (*stack)->node = node;
        (*stack)->next = NULL;
    }
    else {
        add_to_ast_stack(&(*stack)->next, node);
    }
}

/**
 * @fn ast_node_t *pop_ast_stack(ast_stack_t **stack)
 * @brief Pop a node from the AST stack
 * @param stack AST stack
 * @return The popped node
 */
ast_node_t *pop_ast_stack(ast_stack_t **stack) {
    if(stack == NULL) {
        ERROR("pop_ast_stack: stack is NULL");
    }

    if(*stack == NULL) return NULL;

    ast_stack_t *current = *stack;
    *stack = current->next;
    ast_node_t *node = current->node;
    free(current);
    return node;
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

/**********************************************************************************************************************/
/*                                           Private functions definitions                                            */
/**********************************************************************************************************************/
