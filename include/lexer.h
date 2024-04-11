/**
 * @file lexer.h
 * @brief Lexer header file
 * This file contains the definition of the lexer.
 */

#ifndef LEXER_H
#define LEXER_H

#include "common.h"

/**
 * @enum token_type_t
 * @brief Token type enumeration
 * This enumeration defines the different types of tokens.
*/
typedef enum {
    TOKEN_EOF, /*!< End of file token */
    TOKEN_UNKNOWN, /*!< Unknown token */
    TOKEN_IDENTIFIER, /*!< Identifier token */
    TOKEN_NUMBER, /*!< Number token */
    TOKEN_STRING, /*!< String token */
    TOKEN_CHAR, /*!< Character token */
    TOKEN_KEYWORD, /*!< Keyword token */
    TOKEN_OPERATOR, /*!< Operator token */
    TOKEN_SEPARATOR, /*!< Separator token */
    TOKEN_COMMENT, /*!< Comment token */
} token_type_t;

/**
 * @struct token_t
 * @brief Token structure
 * An token is a meaningful sequence of characters in the source code.
 */
typedef struct {
    token_type_t type; /*!< Token type */
    char *text; /*!< Token text */
    size_t textLen; /*!< Token length */
} token_t;

/**
 * @struct lexer_t
 * @brief Lexer structure
 * The Lexer structure contains the state of the lexer.
 */
typedef struct {
    char *content; /*!< Source code content */
    size_t contentLen; /*!< Source code length */
    size_t cursor; /*!< Cursor position */
} lexer_t;

/**
 * @fn lexer_t create_lexer(char *content, size_t contentLen)
 * @brief Create a new lexer
 * @param content Source code content
 * @param contentLen Source code length
 * @return A new lexer
 */
lexer_t create_lexer(char *content, size_t contentLen);

/**
 * @fn token_t next_token(lexer_t *lexer)
 * @brief Get the next token
 * @param lexer Lexer
 * @return The next token
 */
token_t next_token(lexer_t *lexer);


#endif // LEXER_H