#include <string.h>
#include <stdio.h>
#include "runtime.h"
#include "evaluator.h"

void parse_line(const char *line) {
    // Trim leading space
    while (*line == ' ') line++;

    if (strncmp(line, "print(", 6) == 0) {
        const char *start = strchr(line, '(') + 1;
        const char *end = strrchr(line, ')');
        if (start && end && end > start) {
            char buffer[256];
            size_t len = end - start;
            strncpy(buffer, start, len);
            buffer[len] = '\0';

            if (strchr(buffer, '"')) {
                // Print string
                char *str_start = strchr(buffer, '"') + 1;
                char *str_end = strrchr(buffer, '"');
                *str_end = '\0';
                indo_print(str_start);
            } else {
                // Evaluate math expression
                int result = evaluate_expression(buffer);
                char result_str[64];
                snprintf(result_str, sizeof(result_str), "%d", result);
                indo_print(result_str);
            }
        }
    }
}
