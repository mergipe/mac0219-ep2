#include "mtrutils.h"

#include <argp.h>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>

/* Número de argumentos na linha de comando. */
static const int arg_num = 1;

/* Dimensões das matrizes. */
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

/* Mostra a matriz mtr nxn em stdout. */
static void print_matrix(matrix mtr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", mtr[i * n + j]);

        printf("\n");
    }
}

/* Lê o arquivo de matrizes apontado por file, armazena o número de matrizes
 * do arquivo em matrices_num e devolve um vetor com as matrizes lidas. */
static matrix *read_matrices(int *matrices_num, FILE *file)
{
    matrix *matrices;
    char temp[3];

    fscanf(file, "%d", matrices_num);
    matrices = (matrix *) malloc(*matrices_num * sizeof (matrix));

    for (int n = 0; n < *matrices_num; n++)
    {
        matrices[n] = mtralloc(matrices_dim);

        if (matrices[n] == NULL)
        {
            perror("Erro: ");
            exit(EXIT_FAILURE);
        }

        fscanf(file, "%s", temp);

        for (int i = 0; i < matrices_dim; i++)
            for (int j = 0; j < matrices_dim; j++)
                fscanf(file, "%" SCNd32, &matrices[n][i * matrices_dim + j]);
    }

    return matrices;
}

int main(int argc, char **argv)
{
    struct arguments args;
    FILE *matrices_file;
    matrix *matrices;
    int matrices_num;

    argp_parse(&argp, argc, argv, 0, 0, &args);
    matrices_file = fopen(args.args[0], "r");

    if (matrices_file == NULL)
    {
        perror(args.args[0]);
        return EXIT_FAILURE;
    }

    matrices = read_matrices(&matrices_num, matrices_file);
    fclose(matrices_file);

    for (int i = 0; i < matrices_num; i++)
        mtrfree(matrices[i]);
    free(matrices);

    return EXIT_SUCCESS;
}
