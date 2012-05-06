/*
 * 8puzzle
 * main.c
 *
 * @author: Tomáš Maršálek
 * @date: 06.05.2012
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"
#include "pqueue.h"
#include "set.h"

static int start[] = {1, 0, 3,
                      6, 2, 4,
                      8, 7, 5};
static int end[]   = {1, 2, 3,
                      8, 0, 4,
                      7, 6, 5};

/* Program modes. */
static int help = 0;
static int stepping = 0;
static int verbose = 0;
static char *outfile;

static FILE* output;

#define STEP()                                                                \
if (stepping && output == stdout) {                                           \
    printf("Press ENTER to continue...\n");                                   \
    getchar();                                                                \
}

/*
 * Solves the puzzle and prints results.
 * Returns 1 on success and 0 on nonexistence of a solution.
 */
static int solve(int *start, int *end)
{
    Grid *root, *goal, *cur, *child, *iter, **result;
    Pqueue *pq;
    Set *visited;
    int goal_grid_code, child_code;
    int i, ch;
    int path_length;

    root = (Grid *) malloc(sizeof(Grid));
    memcpy(root->g, start, sizeof(int) * 9);
    root->parent = NULL;
    root->hole = 1;
    root->depth = 0;

    goal = (Grid *) malloc(sizeof(Grid));
    memcpy(goal->g, end, sizeof(int) * 9);
    goal_grid_code = grid_code(goal);
    get_correct_positions(goal);

    path_length = 0;
    i = 0;
    pq = pqueue_new();
    visited = set_new(4);
    pqueue_insert(pq, root);
    set_insert(visited, grid_code(root));


    while (!empty(pq)) {
        cur = pqueue_extract_min(pq);
        if (verbose) {
            fprintf(output, "%d.\n", ++i);
            fprintf(output, "Depth: %d\n", cur->depth);
            fprintf(output, "Grid:\n");
            grid_print(output, cur);
            fprintf(output, "f: %2d\n", weight(cur));
            fprintf(output, "\n");
        }
        if (grid_code(cur) == goal_grid_code)
            break;

        ch = 0;

#define ADD_CHILD() {                                                         \
    child_code = grid_code(child);                                            \
    if (!set_contains(visited, child_code)) {                                 \
        set_insert(visited, child_code);                                      \
        pqueue_insert(pq, child);                                             \
        cur->child[ch++] = child;                                             \
    } else                                                                    \
        free(child);                                                          \
}

        /* Hole not on the left wall. */
        if (cur->hole % 3 > 0) {
            child = make_child(cur);
            grid_move_hole(child, child->hole - 1);
            ADD_CHILD();
        }
        /* Hole not on the right wall. */
        if (cur->hole % 3 < 2) {
            child = make_child(cur);
            grid_move_hole(child, child->hole + 1);
            ADD_CHILD();
        }
        /* Hole not on the top wall. */
        if (cur->hole / 3 > 0) {
            child = make_child(cur);
            grid_move_hole(child, child->hole - 3);
            ADD_CHILD();
        }
        /* Hole not on the bottom wall. */
        if (cur->hole / 3 < 2) {
            child = make_child(cur);
            grid_move_hole(child, child->hole + 3);
            ADD_CHILD();
        }
#undef ADD_CHILD

        /* End of children character. */
        cur->child[ch] = NULL;

        if (verbose) {
            fprintf(output, "Children:\n");
            grid_children(output, cur);
            fprintf(output, "------------------------\n");
            fprintf(output, "\n");
            STEP();
        }
    }

    if (grid_code(cur) != goal_grid_code)
        return 0;

    /* Collect result path. */
    for (iter = cur; iter != NULL; iter = iter->parent)
        path_length ++;

    result = (Grid**) malloc(sizeof(Grid*) * path_length);

    i = path_length - 1;
    for (iter = cur; iter != NULL; iter = iter->parent)
        result[i--] = iter;

    if (verbose)
        fprintf(output, "Solution sequence:\n");

    for (i = 0; i < path_length; i++) {
        grid_print(output, result[i]);
        STEP();
        fprintf(output, "\n");
    }


    /* Clean up. */
    grid_dispose(root);
    set_dispose(visited);
    pqueue_dispose(pq);
    free(result);
    free(goal);

    return 1;
}


int main(int argc, char **argv)
{
    int success;

    success = 0;
    output = stdout;

    while (--argc) {
        argv++;
        if (**argv == '-') {
            switch(argv[0][1]) {
                case 'v':
                    verbose = 1;
                    break;
                case 'h':
                    help = 1;
                    break;
                case 's':
                    stepping = 1;
                    break;
                case 'o':
                    argv++;
                    if (--argc)
                        outfile = *argv;
                    else
                        printf("Missing filename.\n");
                    break;
                default:
                    printf("Unknown option: %s\n", *argv);
            }
        }
    }

    if (outfile) {
        output = fopen(outfile, "w");
        if (output == NULL) {
            perror("error opening file\n");
            return EXIT_FAILURE;
        }
    }

    if (help) {
        printf("Usage: 8puzzle [-h|-s|-v] [-o FILE]\n");
        printf("\n");
        printf("\t-h\tHelp.\n");
        printf("\t-s\tStepping mode.\n");
        printf("\t-v\tVerbose output.\n");
        printf("\t-o\tSpecify output file\n");
        return EXIT_SUCCESS;
    }

    success = solve(start, end);
    fclose(output);

    return !success;
}
