/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 02:39:24 by houabell          #+#    #+#             */
/*   Updated: 2025/06/02 02:39:27 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h" // If not already at the top of the file

// Helper to convert token type enum to string for printing
static const char* token_type_to_string(t_token_type type) {
    switch (type) {
        case TOKEN_WORD: return "TOKEN_WORD";
        case TOKEN_PIPE: return "TOKEN_PIPE";
        case TOKEN_REDIR_IN: return "TOKEN_REDIR_IN";
        case TOKEN_REDIR_OUT: return "TOKEN_REDIR_OUT";
        case TOKEN_REDIR_APPEND: return "TOKEN_REDIR_APPEND";
        case TOKEN_HEREDOC: return "TOKEN_HEREDOC";
        case TOKEN_EOF: return "TOKEN_EOF"; // Should not usually appear in active list
        default: return "TOKEN_UNKNOWN";
    }
}

void print_tokens(t_token *tokens) {
    t_token *current = tokens;
    int i = 0;

    printf("\n--- Token List ---\n");
    if (!current) {
        printf(" (empty)\n");
        printf("--------------------\n");
        return;
    }
    while (current) {
        printf("Token %d:\n", i++);
        printf("  Type:  %s\n", token_type_to_string(current->type));
        printf("  Value: [%s]\n", current->value ? current->value : "(null)"); // Handle null value just in case
        current = current->next;
    }
    printf("--------------------\n\n");
}
