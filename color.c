#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int boolean;
#define TRUE 1
#define FALSE 0
#define DEF_KEYWORD_V_MAX 16
#define DEF_COLOR_RED "\033[0;32;31m"
#define DEF_COLOR_NONE "\033[m"

static void _readArgs(int argc, char **argv, char ** keywordv, int keywordMax,
		boolean *pw, boolean *pi) {
	char * arg;
	int i, j;
	int keywordIndex;

	keywordIndex = 0;
	for (i = 1; i < argc; i++) {
		arg = argv[i];
		if (arg[0] == '-') {
			for (j = 1;; j++) {
				if (arg[j] == 0) {
					break;
				} else {
					switch (arg[j]) {
					case 'w':
						*pw = TRUE;
						break;
					case 'i':
						*pi = TRUE;
						break;
					}
				}
			}
		} else {
			if (keywordIndex < keywordMax) {
				keywordv[keywordIndex++] = strdup(arg);
			}
		}
	}
}

static char* _getchunk(FILE *file, int *end) {
	int ch;
	unsigned idx = 0;
	char *linebuf = NULL;

	while ((ch = getc(file)) != EOF) {
		/* grow the line buffer as necessary */
		if (!(idx & 0xff)){
			linebuf = realloc(linebuf, idx + 0x100);
		}
		linebuf[idx++] = (char) ch;

		if (ch == '\0') {
			break;
		}

		if (end && ch == '\n') {
			break;
		}
	}

	if (end) {
		*end = idx;
	}

	if (linebuf) {
		linebuf = realloc(linebuf, idx + 1);
		linebuf[idx] = '\0';
	}
	return linebuf;
}

static char* _getline(FILE *file) {
	int i;
	char *c = _getchunk(file, &i);

	if (i && c[--i] == '\n')
		c[i] = '\0';

	return c;
}

static void _tolowerr(char * str) {
	int i;

	for (i = 0; ; i++) {
		if (str[i] == 0) {
			break;
		}

		str[i] = tolower(str[i]);
	}
}

static void _printf(char * str, char * keyword) {

}

int main(int argc, char **argv) {
	char *keywords[DEF_KEYWORD_V_MAX];
	char *keyword;
	boolean opt_w = FALSE;
	boolean opt_i = FALSE;
	int i;
	char *line, *str;
	FILE *file;

	memset(keywords, 0, sizeof(keywords));
	_readArgs(argc, argv, keywords, DEF_KEYWORD_V_MAX, &opt_w, &opt_i);

	if (opt_i) {
		for (i = 0;; i++) {
			if (keywords[i] == NULL) {
				break;
			}

			_tolowerr(keywords[i]);
		}
	}

	file = stdin;
	while ((line = _getline(file)) != NULL) {
		if (opt_i) {
			_tolower(line);
		}

		for (i = 0;; i++) {
			if (keywords[i] == NULL) {
				break;
			}

			while ((str = strstr(str, keywords[i]))) {

			}


		}



		printf("%s %s\n", DEF_COLOR_RED, line);

		free(line);
	}

	fclose(file);

	for (i = 0;; i++) {
		if (keywords[i] == NULL) {
			break;
		}
		free(keywords[i]);
	}

	return 0;
}
