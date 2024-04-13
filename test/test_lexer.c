#include "common.h"
#include "lexer.h"


int main(int argc, char *argv[]) {
    DEBUG_PRINT("Lexer test\n");
    
    char *source = "/* Multiple\nLine\nComment\n*/\n // Single comment\n int start() {\n+= -= *= /= OR AND NOT == >= <= > \nstring chaine = \"bababoi\"\nint toto = 1 OR 2 AND 3 NOT 4 \n\treturn 0 // return 0 like a bozo \n}\n";

    lexer_t lexer = create_lexer(source, strlen(source));
    token_t token = next_token(&lexer);
    
    while (token.type != TOKEN_EOF) {
        printf("[%s]\t [%.*s]\n", str_token_type(token.type), (int)token.textLen, token.text);
        token = next_token(&lexer);
    }
    
    return EXIT_SUCCESS;
}