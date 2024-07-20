/**
 * @file ast.c
 * @brief Abstract Syntax Tree (AST) implementation
*/
#include "ast.h"

/**********************************************************************************************************************/
/*                                           Private functions signatures                                             */
/**********************************************************************************************************************/

/**
 * @fn void push_ast_stack(linked_list_t *stack, ast_node_t *node)
 * @brief Push a node to the AST stack
 * This function is to avoid casting the node to void * when pushing it to the stack
 */
void push_ast_stack(linked_list_t *stack, ast_node_t *node);


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

    // Add parent to the children nodes
    if(left != NULL) left->parent = node;
    if(right != NULL) right->parent = node;

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

    // Add parent to the children nodes
    if(index != NULL) index->parent = node;

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
 * @fn ast_node_t *create_ast_literal_node(char *value)
 * @brief Create a new AST literal node
 * @param value Literal value
 * @return A new AST literal node
 */
ast_node_t *create_ast_literal_node(char *value) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_LITERAL);
    // Initialize the node
    node->_udata.literal.value = value;
    node->data = &node->_udata.literal;
    return node;
}
/**
 * @fn ast_node_t *create_ast_block_node(ast_node_t **nodes, size_t nodesLen)
 * @brief Create a new AST block node
 * @return A new AST block node
 */
ast_node_t *create_ast_block_node() {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_BLOCK);
    // Initialize the node
    node->_udata.block.nodes = create_linked_list();
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
ast_node_t *create_ast_function_node(char *name, type_type_t type, ast_node_t *body) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_FUNCTION);
    // Add parent to the children nodes
    if(body != NULL) body->parent = node;

    // Initialize the node
    node->_udata.function.name = name;
    node->_udata.function.args = create_linked_list();
    node->_udata.function.body = body;
    node->data = &node->_udata.function;
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
ast_node_t *create_ast_function_call_node(char *name) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_FUNCTION_CALL);
    // Initialize the node
    node->_udata.functionCall.name = name;
    node->_udata.functionCall.args = create_linked_list();
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
    // Add parent to the children nodes
    if(value != NULL) value->parent = node;

    // Initialize the node
    node->_udata.returnNode.value = value;
    node->data = &node->_udata.returnNode;
    return node;
}
/**
 * @fn ast_node_t *create_ast_for_node(ast_node_t *init, ast_node_t *condition, ast_node_t *step, ast_node_t *body)
 * @brief Create a new AST for node
 * @param init Initialization
 * @param condition Condition
 * @param step Step
 * @param body Body
 * @return A new AST for node
 */
ast_node_t *create_ast_for_node(ast_node_t *init, ast_node_t *condition, ast_node_t *step, ast_node_t *body) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_FOR);

    // Add parent to the children nodes
    if(init != NULL) init->parent = node;
    if(condition != NULL) condition->parent = node;
    if(step != NULL) step->parent = node;
    if(body != NULL) body->parent = node;

    // Initialize the node
    node->_udata.forNode.init = init;
    node->_udata.forNode.condition = condition;
    node->_udata.forNode.step = step;
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
    
    // Add parent to the children nodes
    if(condition != NULL) condition->parent = node;
    if(body != NULL) body->parent = node;

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
ast_node_t *create_ast_repeat_until_node(ast_node_t *condition, ast_node_t *body) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_REPEAT_UNTIL);

    // Add parent to the children nodes
    if(condition != NULL) condition->parent = node;
    if(body != NULL) body->parent = node;

    // Initialize the node
    node->_udata.repeatUntilNode.condition = condition;
    node->_udata.repeatUntilNode.body = body;
    node->data = &node->_udata.repeatUntilNode;
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

    // Add parent to the children nodes
    if(variable != NULL) variable->parent = node;
    if(array != NULL) array->parent = node;

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

    // Add parent to the children nodes
    if(condition != NULL) condition->parent = node;
    if(trueBranch != NULL) trueBranch->parent = node;
    if(falseBranch != NULL) falseBranch->parent = node;


    // Initialize the node
    node->_udata.ifNode.condition = condition;
    node->_udata.ifNode.trueBranch = trueBranch;
    node->_udata.ifNode.falseBranch = falseBranch;
    node->data = &node->_udata.ifNode;
    return node;
}

/**
 * @fn ast_node_t *create_ast_var_declaration_node(char *name, type_type_t type, ast_node_t *init)
 * @brief Create a new AST declaration node
 * @param name Variable name
 * @param type Variable type
 * @param init Initialization
 * @return A new AST declaration node
 */
ast_node_t *create_ast_var_declaration_node(char *name, type_type_t type, ast_node_t *init) {
    // Create a new node
    ast_node_t *node = create_ast_node(AST_NODE_VAR_DECLARATION);

    // Add parent to the children nodes
    if(init != NULL) init->parent = node;

    // Initialize the node
    node->_udata.varDeclarationNode.name = name;
    node->_udata.varDeclarationNode.type = type;
    node->_udata.varDeclarationNode.init = init;
    node->data = &node->_udata.varDeclarationNode;
    return node;
}

/**
 * @fn char is_leaf(ast_node_t *node)
 * @brief check if the node is a leaf based on the node type
 * @note a node is considered a leaf if it has a node type greater than AST_NODE_LEAVES
 */
char is_leaf(ast_node_t *node) {
    if(node == NULL) return FALSE;
    return node->type > AST_NODE_LEAVES;
}

/**
 * @fn void free_ast_node(ast_node_t *node)
 * @brief Free an AST node
 * @param node AST node
 * @return void
 */
char free_ast_node(ast_node_t *node) {
    if(node == NULL) return TRUE;

    // Recursively free the children nodes based on the node type
    switch(node->type) {
        case AST_NODE_OPERATOR:
            free_ast_node(node->_udata.operator.left);
            free_ast_node(node->_udata.operator.right);
            break;

        case AST_NODE_VAR_DECLARATION:
            free_ast_node(node->_udata.varDeclarationNode.init);
            break;
        
        case AST_NODE_ARRAY:
            free_ast_node(node->_udata.array.arrayIndex);
            break;
        case AST_NODE_BLOCK:
            free_linked_list(node->_udata.block.nodes, (fn_free_data_t) free_ast_node);
            break;

        case AST_NODE_FUNCTION:
            free_linked_list(node->_udata.function.args, (fn_free_data_t) free_ast_node);
            free_ast_node(node->_udata.function.body);
            break;

        case AST_NODE_FUNCTION_CALL:
            free_linked_list(node->_udata.functionCall.args, (fn_free_data_t) free_ast_node);
            break;

        case AST_NODE_IF:
            free_ast_node(node->_udata.ifNode.condition);
            free_ast_node(node->_udata.ifNode.trueBranch);
            free_ast_node(node->_udata.ifNode.falseBranch);
            break;
        
        case AST_NODE_FOR:
            free_ast_node(node->_udata.forNode.init);
            free_ast_node(node->_udata.forNode.condition);
            free_ast_node(node->_udata.forNode.step);
            free_ast_node(node->_udata.forNode.body);
            break;
        
        case AST_NODE_WHILE:
            free_ast_node(node->_udata.whileNode.condition);
            free_ast_node(node->_udata.whileNode.body);
            break;
        
        case AST_NODE_REPEAT_UNTIL:
            free_ast_node(node->_udata.repeatUntilNode.condition);
            free_ast_node(node->_udata.repeatUntilNode.body);
            break;
        
        case AST_NODE_FOREACH:
            free_ast_node(node->_udata.foreachNode.variable);
            free_ast_node(node->_udata.foreachNode.array);
            free_ast_node(node->_udata.foreachNode.body);
            break;
        
        case AST_NODE_RETURN:
            free_ast_node(node->_udata.returnNode.value);
            break;
        
        default:
            if(node->type < AST_NODE_LEAVES) {
                DEBUG_PRINT("Freeing node type %s is not implemented\n", str_ast_node_type(node->type));
                UNIMPLEMENTED("free_ast_node");
            }
    }
    free(node);

    return TRUE;
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
        case AST_NODE_LITERAL: return "LITERAL";
        case AST_NODE_BLOCK: return "BLOCK";
        case AST_NODE_FUNCTION: return "FUNCTION DEFINITION";
        case AST_NODE_FUNCTION_CALL: return "FUNCTION CALL";
        case AST_NODE_RETURN: return "RETURN";
        case AST_NODE_FOR: return "FOR";
        case AST_NODE_WHILE: return "WHILE";
        case AST_NODE_REPEAT_UNTIL: return "REPEAT UNTIL";
        case AST_NODE_FOREACH: return "FOREACH";
        case AST_NODE_IF: return "IF";
        case AST_NODE_VAR_DECLARATION: return "VARIABLE DECLARATION";
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
        case OP_EQ: return "EQ";
        case OP_NEQ: return "NEQ";
        case OP_GT: return "GT";
        case OP_LT: return "LT";
        case OP_GTE: return "GTE";
        case OP_LTE: return "LTE";
        case OP_AND: return "AND";
        case OP_OR: return "OR";
        case OP_NOT: return "NOT";
        case OP_ASSIGN: return "ASSIGN";
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
    linked_list_t *list = NULL;
    // Check if the parent is a block node
    switch (parent->type)
    {
        case AST_NODE_BLOCK:
            ast_node_block_t *block = (ast_node_block_t *)parent->data;
            list = block->nodes;
            break;
        case AST_NODE_FUNCTION:
            ast_node_function_t *function = (ast_node_function_t *)parent->data;
            list = function->args;
            break;
        case AST_NODE_FUNCTION_CALL:
            ast_node_function_call_t *functionCall = (ast_node_function_call_t *)parent->data;
            list = functionCall->args;
            break;
        default:
            ERROR("Cannot append a child node to a non block node");
            break;
    }
    if(list != NULL) {
        push_linked_list(list, child);
    }
    else {
        ERROR("append_ast_node: list is NULL");
    }
}

/**
 * @fn ast_node_t *next_ast_node(ast_node_t *node, ast_stack_t **stack)
 * @brief Get the next node in the AST tree
 * @param node root node
 * @param stack Stack of nodes
 * @return The next node
 * @note When the function is called for the first time, the stack must be NULL.
 * The stack is used to keep track of the nodes that have been visited.
 * @note The root node is the first node to visit. After the first call, it will not be read again.
 * @note this function return NULL when there is no more node to visit
 * if so, the stack is freed and set to NULL automatically.
 * @warning the stack must not be modified by external functions or the behavior is undefined.
 */
ast_node_t *next_ast_node(ast_iterator_t *iter) {
    linked_list_t *stack = iter->stack;
    ast_node_t *current = iter_linked_list(stack, &iter->current);

    // Variables to iterate over the linked list present in the children nodes
    linked_list_node_t *node = NULL;
    ast_node_t *child = NULL;

    if(current == NULL) {
        return NULL;
    }

    // For each type of node add to the stack the children nodes
    switch(current->type) {
        case AST_NODE_OPERATOR:
            ast_node_operator_t op = *(ast_node_operator_t *)current->data;
            if(op.left != NULL) push_ast_stack(stack, current->_udata.operator.left);
            if(op.right != NULL) push_ast_stack(stack, current->_udata.operator.right);
            break;

        case AST_NODE_ARRAY:
            ast_node_array_t array = *(ast_node_array_t *)current->data;
            if(array.arrayIndex != NULL) push_ast_stack(stack, current->_udata.array.arrayIndex);
            break;

        case AST_NODE_BLOCK:
            ast_node_block_t block = *(ast_node_block_t *)current->data;
            while((child = iter_linked_list(block.nodes, &node))) {
                push_ast_stack(stack, child);
            }
            break;
        
        case AST_NODE_FUNCTION:
            ast_node_function_t function = *(ast_node_function_t *)current->data;
            if(function.body != NULL) push_ast_stack(stack, current->_udata.function.body);
            break;
        
        case AST_NODE_REPEAT_UNTIL:
            ast_node_repeat_until_t repeatUntil = *(ast_node_repeat_until_t *)current->data;
            if(repeatUntil.condition != NULL) push_ast_stack(stack, current->_udata.repeatUntilNode.condition);
            if(repeatUntil.body != NULL) push_ast_stack(stack, current->_udata.repeatUntilNode.body);
            break;
        
        case AST_NODE_FOR:
            ast_node_for_t forNode = *(ast_node_for_t *)current->data;
            if(forNode.init != NULL) push_ast_stack(stack, current->_udata.forNode.init);
            if(forNode.condition != NULL) push_ast_stack(stack, current->_udata.forNode.condition);
            if(forNode.step != NULL) push_ast_stack(stack, current->_udata.forNode.step);
            if(forNode.body != NULL) push_ast_stack(stack, current->_udata.forNode.body);
            break;
        
        case AST_NODE_FOREACH:
            ast_node_foreach_t foreach = *(ast_node_foreach_t *)current->data;
            if(foreach.variable != NULL) push_ast_stack(stack, current->_udata.foreachNode.variable);
            if(foreach.array != NULL) push_ast_stack(stack, current->_udata.foreachNode.array);
            if(foreach.body != NULL) push_ast_stack(stack, current->_udata.foreachNode.body);
            break;
        
        case AST_NODE_FUNCTION_CALL:
            ast_node_function_call_t functionCall = *(ast_node_function_call_t *)current->data;
            while((child = iter_linked_list(functionCall.args, &node))) {
                push_ast_stack(stack, child);
            }
            break;

        case AST_NODE_IF:
            ast_node_if_t ifNode = *(ast_node_if_t *)current->data;
            if(ifNode.condition != NULL) push_ast_stack(stack, current->_udata.ifNode.condition);
            if(ifNode.trueBranch != NULL) push_ast_stack(stack, current->_udata.ifNode.trueBranch);
            if(ifNode.falseBranch != NULL) push_ast_stack(stack, current->_udata.ifNode.falseBranch);
            break;
        
        case AST_NODE_RETURN:
            ast_node_return_t returnNode = *(ast_node_return_t *)current->data;
            if(returnNode.value != NULL) push_ast_stack(stack, current->_udata.returnNode.value);
            break;

        case AST_NODE_WHILE:
            ast_node_while_t whileNode = *(ast_node_while_t *)current->data;
            if(whileNode.condition != NULL) push_ast_stack(stack, current->_udata.whileNode.condition);
            if(whileNode.body != NULL) push_ast_stack(stack, current->_udata.whileNode.body);
            break;
        
        case AST_NODE_VAR_DECLARATION:
            ast_node_var_declaration_t declaration = *(ast_node_var_declaration_t *)current->data;
            if(declaration.init != NULL) push_ast_stack(stack, current->_udata.varDeclarationNode.init);
            break;
        
        // Should be a leaf node
        default:
            break;

    }

    return current;
}


/**
 * @fn gviz_ast_node(ast_node_t *node, FILE *file)
 * @brief Generate a Graphviz file from an AST node
 * @param node AST node
 * @param file File
 * @return void
 */
void gviz_ast_node(ast_node_t *node, FILE *file) {
    if(node == NULL) return;

    ast_iterator_t *iter = create_ast_iterator(node);

    fprintf(file, GVIZ_FILE_HEADER);
    // Go through the AST tree and generate the Graphviz file
    ast_node_t *current = NULL;
    while((current = next_ast_node(iter))) {
        ast_node_t *parent = current->parent;
        char label[100];
        if(is_leaf(current)) {
            switch(current->type) {
                case AST_NODE_VARIABLE:
                    sprintf(label, "%s [%s]", str_ast_node_type(current->type), current->_udata.variable.name);
                    break;
                case AST_NODE_STRING:
                    sprintf(label, "%s ['%s']", str_ast_node_type(current->type), current->_udata.string.value);
                    break;
                case AST_NODE_LITERAL:
                    sprintf(label, "%s [%s]", str_ast_node_type(current->type), current->_udata.literal.value);
                    break;
                case AST_NODE_ARRAY:
                    sprintf(label, "%s [%s]", str_ast_node_type(current->type), current->_udata.array.name);
                    break;
                default:
                    sprintf(label, "%s", str_ast_node_type(current->type));
                    break;
            }
        } else {
            if(current->type == AST_NODE_OPERATOR) {
                sprintf(label, "%s [%s]", str_ast_node_type(current->type), str_op_type(current->_udata.operator.type));
            } else
            sprintf(label, "%s", str_ast_node_type(current->type));
        }
        GVIZ_ADD_NODE(file, current, is_leaf(current) ? GVIZ_LEAF_NODE_STYLE : GVIZ_INTERNAL_NODE_STYLE, label);
        if(parent != NULL) {
            GVIZ_ADD_EDGE_TEXT(file, current->parent, current, get_edge_label(parent, current));
        }
    }
    fprintf(file, GVIZ_FILE_FOOTER);
    free_ast_iterator(iter);
}

/**
 * @fn ast_iterator_t *create_ast_iterator(ast_node_t *root)
 * @brief Create a new AST iterator
 * @param root Root node
 * @return A new AST iterator
 * @note The iterator is initialized to the first node of the tree
 */
ast_iterator_t *create_ast_iterator(ast_node_t *root) {
    ast_iterator_t *iter = (ast_iterator_t *)malloc(sizeof(ast_iterator_t));
    CHECK_ALLOC(iter, "create_ast_iterator: iter");
    iter->stack = create_linked_list();
    push_ast_stack(iter->stack, root);
    iter->current = NULL;
    return iter;
}

/**
 * @fn void free_ast_iterator(ast_iterator_t *iter)
 * @brief Free an AST iterator
 * @param iter AST iterator
 * @return void
 */
void free_ast_iterator(ast_iterator_t *iter) {
    free_linked_list(iter->stack, NULL);
    free(iter);
}

/**
 * @char *get_edge_label(ast_node_t *parent, ast_node_t *child)
 * @brief Get the label of the edge between two nodes
 * @param parent Parent node
 * @param child Child node
 * @return The label of the edge
 * @warning the label is allocated on the heap and must be freed by the user
 */
const char *get_edge_label(ast_node_t *parent, ast_node_t *child) {
    switch(parent->type) {
        case AST_NODE_BLOCK:
            return ""; // no label for block nodes edges
        case AST_NODE_FUNCTION:
            if(parent->_udata.function.body == child) return "body";
            return ""; // no label for function nodes edges

        case AST_NODE_FUNCTION_CALL:
            return ""; // no label for function call nodes edgess

        case AST_NODE_RETURN:
            return ""; // no label for return nodes edges

        case AST_NODE_VAR_DECLARATION:
            if(parent->_udata.varDeclarationNode.init == child) {
                return "init";
            }
            return ""; // no label for variable declaration nodes edges

        case AST_NODE_FUNCTION_DECLARATION:
            return ""; // no label for function declaration nodes edges

        case AST_NODE_FOR:
            if(parent->_udata.forNode.init == child) return "init";
            if(parent->_udata.forNode.condition == child) return "condition";
            if(parent->_udata.forNode.step == child) return "step";
            return "body";

        case AST_NODE_WHILE:
            if(parent->_udata.whileNode.condition == child) return "condition";
            return "body";
        case AST_NODE_REPEAT_UNTIL:
            if(parent->_udata.repeatUntilNode.condition == child) return "condition";
            return "body";
        case AST_NODE_FOREACH:
            if(parent->_udata.foreachNode.variable == child) return "variable";
            if(parent->_udata.foreachNode.array == child) return "array";
            return "body";
        
        case AST_NODE_IFNT:
        case AST_NODE_IF:
            if(parent->_udata.ifNode.condition == child) return "condition";
            if(parent->_udata.ifNode.trueBranch == child) return "true-branch";
            return "false-branch";

        case AST_NODE_OPERATOR:
            if(parent->_udata.operator.left == child) return "left";
            return "right";

        default:
            return "";
    }
}

/**********************************************************************************************************************/
/*                                           Private functions definitions                                            */
/**********************************************************************************************************************/

/**
 * @fn void push_ast_stack(linked_list_t *stack, ast_node_t *node)
 * @brief Push a node to the AST stack
 * This function is to avoid casting the node to void * when pushing it to the stack
 */
void push_ast_stack(linked_list_t *stack, ast_node_t *node) {
    push_linked_list(stack, (void *)node);
}