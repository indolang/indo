#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "evaluator.h"

#define MAX_TOKENS 256

typedef enum { TOKEN_NUMBER, TOKEN_OPERATOR, TOKEN_LPAREN, TOKEN_RPAREN } TokenType;

typedef struct {
    TokenType type;
    char op;
    int value;
} Token;

static int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': case '%': return 2;
        default: return 0;
    }
}

static int apply_operator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b ? a / b : 0;
        case '%': return b ? a % b : 0;
        case '<': return a < b;
        case '>': return a > b;
        case '=': return a == b;
        default: return 0;
    }
}

int evaluate_expression(const char *expr) {
    Token output[MAX_TOKENS], stack[MAX_TOKENS];
    int out_len = 0, stack_len = 0;
    const char *p = expr;

    // Shunting-yard algorithm
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        } else if (isdigit(*p)) {
            int val = strtol(p, (char**)&p, 10);
            output[out_len++] = (Token){.type = TOKEN_NUMBER, .value = val};
        } else if (*p == '(') {
            stack[stack_len++] = (Token){.type = TOKEN_LPAREN};
            p++;
        } else if (*p == ')') {
            while (stack_len > 0 && stack[stack_len - 1].type != TOKEN_LPAREN) {
                output[out_len++] = stack[--stack_len];
            }
            if (stack_len > 0) stack_len--; // pop left paren
            p++;
        } else if (strchr("+-*/%<>=", *p)) {
            char op = *p++;
            while (stack_len > 0 && stack[stack_len - 1].type == TOKEN_OPERATOR &&
                   precedence(stack[stack_len - 1].op) >= precedence(op)) {
                output[out_len++] = stack[--stack_len];
            }
            stack[stack_len++] = (Token){.type = TOKEN_OPERATOR, .op = op};
        } else {
            p++; // skip unknown char
        }
    }
    while (stack_len > 0) output[out_len++] = stack[--stack_len];

    // Evaluate RPN
    int eval_stack[MAX_TOKENS], eval_len = 0;
    for (int i = 0; i < out_len; i++) {
        if (output[i].type == TOKEN_NUMBER) {
            eval_stack[eval_len++] = output[i].value;
        } else if (output[i].type == TOKEN_OPERATOR) {
            if (eval_len < 2) return 0;
            int b = eval_stack[--eval_len];
            int a = eval_stack[--eval_len];
            eval_stack[eval_len++] = apply_operator(a, b, output[i].op);
        }
    }
    return eval_len == 1 ? eval_stack[0] : 0;
}
