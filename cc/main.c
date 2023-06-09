#include "cc.h"

#include "test.inc"

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "test") == 0) {
        execute_test();
        return 0;
    }

    if (argc < 3 || argc > 4) goto usage;

    char *infile = argv[1], *outfile = argv[2];

    Vector *tokens = read_tokens_from_filepath(infile);
    tokens = preprocess_tokens(tokens);
    tokens = concatenate_string_literal_tokens(tokens);

    Vector *asts = parse_prog(tokens);

    Env *env = analyze_ast(asts);

    if (argc == 4 && strcmp(argv[3], "--arch=SIMPLE") == 0) {
        // SIMPLE architecture
        Vector *code = SIMPLE_generate_code(asts);

        FILE *fh = fopen(outfile, "wb");
        for (int i = 0; i < vector_size(code); i++)
            SIMPLE_dump_code((SIMPLECode *)vector_get(code, i), fh);
        fclose(fh);
    }
    else {
        // x86_64 architecture
        x86_64_optimize_asts_constant(asts, env);
        Vector *code = x86_64_generate_code(asts);
        code = x86_64_optimize_code(code);

        FILE *fh = fopen(outfile, "wb");
        for (int i = 0; i < vector_size(code); i++)
            dump_code((Code *)vector_get(code, i), fh);
        fclose(fh);
    }

    return 0;

usage:
    error("Usage: cc input-c-file-path output-asm-file-path --arch=SIMPLE");
}
