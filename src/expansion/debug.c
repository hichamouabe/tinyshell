/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 02:36:23 by houabell          #+#    #+#             */
/*   Updated: 2025/06/02 02:36:47 by houabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Helper to convert quote type enum to string for printing
static const char* quote_type_to_string(t_quote_type type) {
    switch (type) {
        case QUOTE_NONE: return "QUOTE_NONE";
        case QUOTE_SINGLE: return "QUOTE_SINGLE";
        case QUOTE_DOUBLE: return "QUOTE_DOUBLE";
        default: return "QUOTE_UNKNOWN";
    }
}

void print_variables(t_var_info *variables) {
    t_var_info *current = variables;
    int i = 0;

    printf("\n--- Logged Variables for Expansion ---\n");
    if (!current) {
        printf(" (none logged)\n");
        printf("--------------------------------------\n");
        return;
    }
    while (current) {
        printf("Variable %d:\n", i++);
        printf("  Name:    [%s]\n", current->name ? current->name : "(null)");
        printf("  Length:  %zu\n", current->length);
        printf("  Context: %s\n", quote_type_to_string(current->quote_context));
        current = current->next;
    }
    printf("--------------------------------------\n\n");
}
