#include "ui.h"

FILE *currentFile;
Drive *currentDrive;

char **parse_command(char *command) {
  const char whitespace[7] = " \t\n\v\f\r";
  char *token;

  char *cmd;
  cmd = malloc(strlen(command));
  strncpy(cmd, command, strlen(command));

  // count tokens, start with first
  int count = 1;
  token = strtok(command, whitespace);

  /* walk through other tokens */
  while (token != NULL) {
    token = strtok(NULL, whitespace);
    count++;
  }
  char **ret = malloc((count + 1) * sizeof(char *));
  ret[count] = malloc(1);
  ret[count] = NULL;

  // read first token into ret
  token = strtok(cmd, whitespace);
  ret[0] = malloc(strlen(token));
  strncpy(ret[0], token, strlen(token));
  token = strtok(NULL, whitespace);
  count = 1;

  /* walk through other tokens */
  while (token != NULL) {
    ret[count] = malloc(strlen(token));
    strncpy(ret[count], token, 20);
    count++;
    token = strtok(NULL, whitespace);
  }

  return ret;
}

void import_file(char **tokens, Drive *d) {
  // Copy a file stored in the regular file system to the current TFS-disk. For
  // part 1, LP is ignored, and an empty file is created at location tp.

  // steps
  // find first free block pointer in the directory from the bitmap
  // update the bitmap, write the file name in the correct byte
}

void ls(char **tokens) {
  // maybe do strtok to break up names for path.
  char *names;

  //  list the contents of the given directory of the TFS-disk
  // steps:
  // confirm the path tp points to a valid directory, if not report error
  int currentIndex = 0;
  for (int i = 0; i < strnlen(names, 8); i++) {
    int entryIndex = 3;
    char currentEntry = currentDrive->block[currentIndex][entryIndex];
    while (entryIndex < 11 && currentEntry != names[i]) {
      char currentEntry = currentDrive->block[currentIndex][entryIndex];
    }
    if (currentEntry !=) {
    }
  }

  // use the directory's bitmap to determine which entries are valid
  // print out the one character names of the valid entries

  // int dirIndex = 0;
  // int entryIndex = 3;

  // char currentEntry = currentDrive->block[dirIndex][entryIndex];
  // while(entryIndex = )
}

void openFile(char **tokens) {
  // close the TFS-file currently in use, if any
  if (currentFile != NULL)
    fclose(currentFile);
  // open an existing TFS-disk file, fails if file DNE
  currentFile = fopen(tokens[1], "r+");
  if (currentFile == NULL) {
    printf("Error, file invalid.\n");
    return;
  }
  // make sure size of file is valid
  struct stat myInode;
  int ret = stat(tokens[1], &myInode);
  int fileSize = myInode.st_size;
  if (fileSize == 256) {
    // TODO: read the file into a Disk struct
    for (int i = 0; i < 16; i++) {
      currentDrive = newDrive(); // idk that we need to reset
      fread(currentDrive->block[i], 1, 16, currentFile);
    }
  } else {
    printf("Error, file invalid.\n");
  }
}

void create(char **tokens, Drive *d) {
  // if file exists, display error
  if (access(tokens[1], F_OK) == 0) {
    printf("Error, file already exists.\n");
    return;
  }
  // create empty disk in memory
  currentFile = fopen(tokens[1], "r+");
  currentDrive = newDrive();
  // save it to the given file name
  fwrite(dump, 256, 1, currentFile); // TODO: this is prob wrong
}

void makeDirectory(char **tokens, Drive *d) {
  // Create a new directory in the TFS-disk.

  // steps:
  // confirm there is a free block in the root freespace bitmap

  // TODO: potentially use isopen for this and finding block for new dir

  // confirm the path tp points to a valid location for a new directory
  // use the freespace bitmap to find a block for the new directory
  // use the parent directory bitmap to find an entry for tp
  // update the freespace bitmap to remove the selected block
  // update the parent directory bitmap, name, and block pointer: tp
  // initialize the bitmap and parent pointer of the new directory block
}

void removeFromTFS(char **tokens, Drive *d) {
  // Remove a file or directory from the TFS-disk. Fails if the file or
  // directory does not exist, or if the directory is not empty.

  // steps:
  // confirm tp is valid, else error
  // update parent directory bitmap
  // update freespace bitmap
}