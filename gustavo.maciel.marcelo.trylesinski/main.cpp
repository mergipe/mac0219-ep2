#include "mtrutils.h"
#include "reduce.cuh"

#include <argp.h>
#include <cstdio>
#include <cstdlib>

// Número de argumentos na linha de comando.
static const int arg_num = 1;

// Dimensões das matrizes.
static const int matrices_dim = 3;

static char doc[] =
    "This program ...\v"
    "...";

static char args_doc[] = "MATRICES_FILE";

static struct argp_option options[] = 
{
    {0,               0,  0, 0,               "ARGS:"},
    {"MATRICES_FILE", 0,  0, OPTION_DOC |
                             OPTION_NO_USAGE, "Path to the matrices file"},
    {0}
};

struct arguments
{
    char *args[1];
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = (struct arguments *) state->input;

    switch(key)
    {
        case ARGP_KEY_ARG:
            if (state->arg_num >= arg_num)
                argp_state_help(state, stderr, ARGP_HELP_STD_HELP);
            arguments->args[state->arg_num] = arg;
            break;

        case ARGP_KEY_END:
            if (state->arg_num < arg_num)
                argp_state_help(state, stderr, ARGP_HELP_STD_HELP);
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv)
{
    struct arguments args;
    FILE *matrices_file;
    matrix *matrices, result;
    int matrices_num;

    argp_parse(&argp, argc, argv, 0, 0, &args);
    matrices_file = fopen(args.args[0], "r");

    if (matrices_file == NULL)
    {
        perror(args.args[0]);
        return EXIT_FAILURE;
    }

    matrices = read_matrices(&matrices_num, matrices_dim, matrices_file);
    fclose(matrices_file);
    result = mtralloc(matrices_dim);
    cuda_reduce(matrices, result, matrices_dim);
    print_matrix(result, matrices_dim);

    for (int i = 0; i < matrices_num; i++)
        mtrfree(matrices[i]);
    free(matrices);
    mtrfree(result);

    return EXIT_SUCCESS;
}
