#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Tokens (トークンの種類を定義)
enum { TOKEN_NUM, TOKEN_PLUS, TOKEN_MINUS, TOKEN_MUL, TOKEN_DIV, TOKEN_EOF };

// Current token (現在のトークンと数値)
int token;
int number;
char* input; // 入力文字列
char* start_input; // 入力文字列の先頭

// 次のトークンを読み取る関数
void next_token() {
    // 空白をスキップ
    while (isspace(*input)) input++;
    // 数字であれば、数値を読み取り
    if (isdigit(*input)) {
        number = strtol(input, &input, 10);
        token = TOKEN_NUM;
    } else {
        // 演算子またはEOFを読み取り
        switch (*input) {
            case '+': token = TOKEN_PLUS; break;
            case '-': token = TOKEN_MINUS; break;
            case '*': token = TOKEN_MUL; break;
            case '/': token = TOKEN_DIV; break;
            case '\0': token = TOKEN_EOF; break;
            default: printf("Unexpected character: %c at position %ld\n", *input, input - start_input + 1); exit(1);
        }
        input++;
    }
}

// 因子を解析（ここでは数字のみ）
int factor() {
    int result = number;
    next_token();
    return result;
}

// 項を解析（乗算と除算を処理）
int term() {
    int result = factor();
    while (token == TOKEN_MUL || token == TOKEN_DIV) {
        if (token == TOKEN_MUL) {
            next_token();
            result *= factor();
        } else {
            next_token();
            result /= factor();
        }
    }
    return result;
}

// 式を解析（加算と減算を処理）
int expr() {
    int result = term();
    while (token == TOKEN_PLUS || token == TOKEN_MINUS) {
        if (token == TOKEN_PLUS) {
            next_token();
            result += term();
        } else {
            next_token();
            result -= term();
        }
    }
    return result;
}

// メイン関数
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }
    input = argv[1];
    start_input = argv[1];
    next_token(); // 最初のトークンを読み取り
    printf("%d \n", expr()); // 式を評価し、結果を表示
    return 0;
}
