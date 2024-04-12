/**
 * @file lexer.c
 * @brief Lexer implementation
 * 
*/
#include "lexer.h"

/**********************************************************************************************************************/
/*                                           Private functions signatures                                             */
/**********************************************************************************************************************/

/**
 * @fn skip_whitespace(lexer_t *lexer)
 * @brief Skip whitespace characters in the source code
 * @param lexer Lexer
 * @return void
*/
void skip_whitespace(lexer_t *lexer);

/**
 * @fn skip_comment(lexer_t *lexer)
 * @brief Skip comments in the source code
 * @param lexer Lexer
 * @return void
*/
void skip_comment(lexer_t *lexer);

/**
 * @fn read_identifier(lexer_t *lexer, token_t *token)
 * @brief Read an identifier from the source code
 * An identifier is a sequence of letters, digits and underscores that does not start with a digit
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_identifier(lexer_t *lexer, token_t *token);

/**
 * @fn read_number(lexer_t *lexer, token_t *token)
 * @brief Read a number from the source code
 * A number is a sequence of digits
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_number(lexer_t *lexer, token_t *token);

/**
 * @fn read_string(lexer_t *lexer, token_t *token)
 * @brief Read a string from the source code
 * A string is a sequence of characters enclosed in double quotes
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_string(lexer_t *lexer, token_t *token);

/**
 * @fn read_char(lexer_t *lexer, token_t *token)
 * @brief Read a character from the source code
 * A character is a single character enclosed in single quotes
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_char(lexer_t *lexer, token_t *token);

/**
 * @fn read_operator(lexer_t *lexer, token_t *token)
 * @brief Read an operator from the source code
 * An operator is a sequence of special characters
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_operator(lexer_t *lexer, token_t *token);

/**
 * @fn custom_strnstr(const char *haystack, const char *needle)
 * @brief Custom implementation of strnstr for non-NULL terminated strings
 * @param haystack Haystack string
 * @param needle Needle string
 * @param needleLen Needle string length
 * @return Pointer to the first occurrence of the needle in the haystack
*/
char *custom_strnstr(const char *haystack, const char *needle, size_t needleLen);

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

    int currCursor;

    // First we skip whitespace characters
    skip_whitespace(lexer);
    // Then we skip comments if any
    skip_comment(lexer);
    // We save the current cursor position for readability
    currCursor = lexer->cursor;
    token.text = lexer->content + currCursor;

    // Check if there is no more content
    if(lexer->cursor >= lexer->contentLen) {
        return token;
    }

    // Check if the current character is an identifier
    if(isalpha(lexer->content[currCursor])) {
        read_identifier(lexer, &token);
        return token;
    }

    // Check if the current character is a number
    if(isdigit(lexer->content[currCursor])) {
        read_number(lexer, &token);
        return token;
    }
    // Check if the current character is a string
    if(lexer->content[currCursor] == '"') {
        read_string(lexer, &token);
        return token;
    }
    // Check if the current character is a character
    if(lexer->content[currCursor] == '\'') {
        read_char(lexer, &token);
        return token;
    }
    // Check if the current character is an separator
    if(lexer->content[currCursor] == '(' || lexer->content[currCursor] == ')' || lexer->content[currCursor] == '{' || lexer->content[currCursor] == '}' || lexer->content[currCursor] == ',') {
        token.type = TOKEN_SEPARATOR;
        lexer->cursor++;
        token.textLen = 1;
        return token;
    }

    // At this point we don't know what the token is
    token.type = TOKEN_UNKNOWN;
    lexer->cursor++;
    return token;
}

/**
 * @fn void print_token_type(token_type_t type)
 * @brief Print a token type
 * @param type Token type
 * @return void
 */
const char *str_token_type(token_type_t type) {
    switch(type) {
        case TOKEN_EOF: /*!< End of file token */
            return "EOF";
        case TOKEN_UNKNOWN: /*!< Unknown token */
            return "UNKNOWN";
        case TOKEN_IDENTIFIER: /*!< Identifier token */
            return "IDENTIFIER";
        case TOKEN_NUMBER: /*!< Number token */
            return "NUMBER";
        case TOKEN_STRING: /*!< String token */
            return "STRING";
        case TOKEN_CHAR: /*!< Character token */
            return "CHAR";
        case TOKEN_KEYWORD: /*!< Keyword token */
            return "KEYWORD";
        case TOKEN_OPERATOR: /*!< Operator token */
            return "OPERATOR";
        case TOKEN_SEPARATOR: /*!< Separator token */
            return "SEPARATOR";
        case TOKEN_COMMENT: /*!< Comment token */
            return "COMMENT";
    }
    return "UNKNOWN";
}

/**********************************************************************************************************************/
/*                                           Private functions definitions                                            */
/**********************************************************************************************************************/

/**
 * @fn skip_whitespace(lexer_t *lexer)
 * @brief Skip whitespace characters in the source code
 * @param lexer Lexer
 * @return void
*/
void skip_whitespace(lexer_t *lexer) {
    // First we check out of bounds
    // Then we check if the current character is a whitespace character (space, tab, newline)
    while(lexer->cursor < lexer->contentLen && (lexer->content[lexer->cursor] == ' ' || lexer->content[lexer->cursor] == '\t' || lexer->content[lexer->cursor] == '\n')) {
        // if so we move to the next character
        lexer->cursor++;
    }
    // cursor is now at the first non-whitespace character
}

/**
 * @fn skip_comment(lexer_t *lexer)
 * @brief Skip comments in the source code
 * @param lexer Lexer
 * @return void
*/
void skip_comment(lexer_t *lexer) {
    // There are two types of comments in Lukakou :
    // - Single line comments starting with //
    // - Multi-line comments starting with /* and ending with */

    // First we check if the current character is a /
    while(lexer->content[lexer->cursor] == '/') {
        // Check if single line comment
        if(lexer->cursor + 1 < lexer->contentLen && lexer->content[lexer->cursor + 1] == '/') {
            while(lexer->cursor < lexer->contentLen && lexer->content[lexer->cursor] != '\n') {
                lexer->cursor++;
            } 
        // Check if multi-line comment
        } else if(lexer->cursor + 1 < lexer->contentLen && lexer->content[lexer->cursor + 1] == '*') {
            lexer->cursor += 2;
            // We look for the end of the comment
            while(lexer->cursor < lexer->contentLen && !(lexer->content[lexer->cursor] == '*' && lexer->content[lexer->cursor + 1] == '/')) {
                lexer->cursor++;
            }
            // We move the cursor to the character after the end of the comment
            lexer->cursor += 2;
        }
        skip_whitespace(lexer);
    }
}

/**
 * @fn read_identifier(lexer_t *lexer, token_t *token)
 * @brief Read an identifier from the source code
 * An identifier is a sequence of letters, digits and underscores that does not start with a digit
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_identifier(lexer_t *lexer, token_t *token) {
    // We look for the end of the identifier
    while(lexer->cursor < lexer->contentLen && (isalnum(lexer->content[lexer->cursor]) || lexer->content[lexer->cursor] == '_')) {
        lexer->cursor++;
    }
    
    // We set the token text length
    token->textLen = lexer->cursor - (token->text - lexer->content);

    // The actual text may be a keyword so we check if it is
    if(custom_strnstr(KEYWORDS, token->text, token->textLen) != NULL) {
        // We set the token type to TOKEN_KEYWORD
        token->type = TOKEN_KEYWORD;
    } else {
        // We set the token type to TOKEN_IDENTIFIER
        token->type = TOKEN_IDENTIFIER;
    }
}

/**
 * @fn read_number(lexer_t *lexer, token_t *token)
 * @brief Read a number from the source code
 * A number is a sequence of digits
 * @param lexer Lexer
 * @param token Token
 * @return void
 */
void read_number(lexer_t *lexer, token_t *token) {
    // We move to the next character
    lexer->cursor++;
    // We look for the end of the number
    while (lexer->cursor < lexer->contentLen && isdigit(lexer->content[lexer->cursor])) {
        lexer->cursor++;
    }
    // We set the token type to TOKEN_NUMBER
    token->type = TOKEN_NUMBER;
    // We set the token text length
    token->textLen = lexer->cursor - (token->text - lexer->content);
}

/**
 * @fn read_string(lexer_t *lexer, token_t *token)
 * @brief Read a string from the source code
 * A string is a sequence of characters enclosed in double quotes
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_string(lexer_t *lexer, token_t *token) {
    // First we check if the current character is a "
    if(lexer->content[lexer->cursor] == '"') {
        // We move to the next character
        lexer->cursor++;
        // We look for the end of the string
        while(lexer->cursor < lexer->contentLen && lexer->content[lexer->cursor] != '"') {
            lexer->cursor++;
        }
        // We move to the next character
        lexer->cursor++;
        // We set the token type to TOKEN_STRING
        token->type = TOKEN_STRING;
        // We set the token text length
        token->textLen = lexer->cursor - (token->text - lexer->content);
    }
}

/**
 * @fn read_char(lexer_t *lexer, token_t *token)
 * @brief Read a character from the source code
 * A character is a single character enclosed in single quotes
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_char(lexer_t *lexer, token_t *token) {
    // First we check if the current character is a '
    if(lexer->content[lexer->cursor] == '\'') {
        // We move to the next character
        lexer->cursor++;
        // We look for the end of the character
        while(lexer->cursor < lexer->contentLen && lexer->content[lexer->cursor] != '\'') {
            lexer->cursor++;
        }
        // We move to the next character
        lexer->cursor++;
        // We set the token type to TOKEN_CHAR
        token->type = TOKEN_CHAR;
        // We set the token text length
        token->textLen = lexer->cursor - (token->text - lexer->content);
    }

}

/**
 * @fn read_operator(lexer_t *lexer, token_t *token)
 * @brief Read an operator from the source code
 * An operator is a sequence of special characters
 * @param lexer Lexer
 * @param token Token
 * @return void
*/
void read_operator(lexer_t *lexer, token_t *token) {
    UNIMPLEMENTED("read_operator");
}


/**
 * @fn custom_strnstr(const char *haystack, const char *needle)
 * @brief Custom implementation of strnstr for non-NULL terminated strings
 * @param haystack Haystack string
 * @param needle Needle string
 * @param needleLen Needle string length
 * @return Pointer to the first occurrence of the needle in the haystack
*/
char *custom_strnstr(const char *haystack, const char *needle, size_t needleLen) {
    if(needleLen == 0) {
        return NULL;
    }

    while(*haystack) {
        if(*haystack == *needle) {
            if(strncmp(haystack, needle, needleLen) == 0) {
                return (char *)haystack;
            }
        }
        haystack++;
    }

    return NULL;
}