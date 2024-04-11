/**
 * @file lexer.c
 * @brief Lexer implementation
 * 
*/
#include "lexer.h"

/**********************************************************************************************************************/
/*                                           Private functions signatures                                             */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/*                                           Public functions definitions                                             */
/**********************************************************************************************************************/

/**
 * @fn lexer_t create_lexer(char *content, size_t contentLen)
 * @brief Create a new lexer
 * @param content Source code content
 * @param contentLen Source code length
 * @return A new lexer
 */
lexer_t create_lexer(char *content, size_t contentLen) {
    lexer_t lexer = {
        .content = content,
        .contentLen = contentLen,
        .cursor = 0
    };

    return lexer;
}

/**
 * @fn token_t next_token(lexer_t *lexer)
 * @brief Get the next token
 * @param lexer Lexer
 * @return The next token
 */
token_t next_token(lexer_t *lexer) {
    token_t token = {
        .type = TOKEN_EOF,
        .text = lexer->content + lexer->cursor, 
        .textLen = 0
    };
    UNIMPLEMENTED("next_token");
    return token;

}

/**********************************************************************************************************************/
/*                                           Private functions definitions                                            */
/**********************************************************************************************************************/