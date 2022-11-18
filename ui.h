#include "drive.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char **parse_command(char *command);
void import_file(char **tokens, Drive *d);
void ls(Drive *d);