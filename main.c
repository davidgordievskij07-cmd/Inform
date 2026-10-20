#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "stack.h"

#define MAX_LINE_LENGTH 1000

typedef enum {
    BALANCED,
    NOT_BALANCED,
    MEMORY_ERROR
} CheckResult;

bool isOpenBracket(char symbol)
{
    return symbol == '(' || symbol == '[' || symbol == '{';
}

bool isCloseBracket(char symbol)
{
    return symbol == ')' || symbol == ']' || symbol == '}';
}

char matchingOpenBracket(char closeBracket)
{
    switch (closeBracket) {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    default:
        return '\0';
    }
}

CheckResult checkBrackets(const char *string)
{
    Stack stack = { NULL };

    for (int i = 0; string[i] != '\0'; ++i) {
        char symbol = string[i];

        if (isOpenBracket(symbol)) {
            if (!push(&stack, symbol)) {
                clear(&stack);
                return MEMORY_ERROR;
            }
        } else if (isCloseBracket(symbol)) {
            if (isEmpty(&stack) || pop(&stack) != matchingOpenBracket(symbol)) {
                clear(&stack);
                return NOT_BALANCED;
            }
        }
    }

    bool allClosed = isEmpty(&stack);
    clear(&stack);
    return allClosed ? BALANCED : NOT_BALANCED;
}

bool runTests(void)
{
    const char *balancedStrings[] = {
        "", "()", "[]{}", "([]{})", "{[()()]}", "a(b + c) * [d - {e}]", "((()))"
    };
    const char *notBalancedStrings[] = {
        "(", ")", "(]", "([)]", "(()", "())", "}{", "{[}]", "abc)"
    };
    int balancedCount = sizeof(balancedStrings) / sizeof(balancedStrings[0]);
    int notBalancedCount = sizeof(notBalancedStrings) / sizeof(notBalancedStrings[0]);

    bool allPassed = true;
    for (int i = 0; i < balancedCount; ++i) {
        if (checkBrackets(balancedStrings[i]) != BALANCED) {
            printf("Тест не пройден: \"%s\" должна быть сбалансирована\n", balancedStrings[i]);
            allPassed = false;
        }
    }
    for (int i = 0; i < notBalancedCount; ++i) {
        if (checkBrackets(notBalancedStrings[i]) != NOT_BALANCED) {
            printf("Тест не пройден: \"%s\" не должна быть сбалансирована\n", notBalancedStrings[i]);
            allPassed = false;
        }
    }
    return allPassed;
}

int main(void)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    if (!runTests()) {
        return 1;
    }

    printf("Введите строку (не длиннее %d символов): ", MAX_LINE_LENGTH);
    char line[MAX_LINE_LENGTH + 2];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("Не удалось прочитать строку\n");
        return 1;
    }

    switch (checkBrackets(line)) {
    case BALANCED:
        printf("Скобки расставлены правильно\n");
        break;
    case NOT_BALANCED:
        printf("Скобки расставлены неправильно\n");
        break;
    case MEMORY_ERROR:
        printf("Не хватило памяти\n");
        return 1;
    }
    return 0;
}