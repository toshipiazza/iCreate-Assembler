#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parser/assembler.tab.h"

char *usage = "USAGE: %s [-h] infile [-o outfile]\n";
char *outfile = "a.out";
extern FILE *yyin;

int
main(int argc, char **argv)
{
  int c;
  while ((c = getopt(argc, argv, "hxo:")) != -1)
    switch (c) {
    case 'h':
      fprintf(stderr, usage, argv[0]);
      return EXIT_FAILURE;
    case 'o':
      outfile = optarg;
      break;
    case '?':
      if (optopt == 'o')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option '-%c'.\n", optopt);
      else
        fprintf(stderr,
                "Unknown option character '\\x%x'.\n",
                (unsigned int) optopt);
      return EXIT_FAILURE;
    default:
      abort(); // lol
    }

  if (argc - optind != 1) {
    fprintf(stderr, "ERROR: INVALID ARGUMENTS\n");
    fprintf(stderr, usage, argv[0]);
    return EXIT_FAILURE;
  }

  yyin = fopen(argv[optind], "r");
  if (!yyin) {
    fprintf(stderr, "ERROR: INFILE\n%s: ", argv[optind]);
    perror("");
    return EXIT_FAILURE;
  }

  yyparse();
  fclose(yyin);
  return EXIT_SUCCESS;
}
