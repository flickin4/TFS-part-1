#include "ui.h"

int currentFile = -1;
Drive *currentDrive;

char **parse_command(char *command, char *whitespace) {
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

void import_file(char **tokens) {
  // bullshitting this for now and pretending 1 is directory name and 2 is file
  // name.

  // Copy a file stored in the regular file system to the current TFS-disk. For
  // part 1, LP is ignored, and an empty file is created at location tp.

  // steps
  // find first free block pointer in the directory from the bitmap
  // update the bitmap, write the file name in the correct byte
}

void list_contents(char **tokens) {
  // maybe do strtok to break up names for path.
  // char *names;
  // char DirName = strtok()

  // list the contents of the given directory of the TFS-disk
  // steps:
  // confirm the path tp points to a valid directory, if not report error
  printf("inside list_contents");
  fflush(stdout);
  // printf(tokens[1]);

  // int pathSize = sizeof(tokens[2]);
  // printf("inside list_contents2");
  // fflush(stdout);
  // printf("%d\n", pathSize);
  // fflush(stdout);

  // char idk[15];
  // strncpy(&idk, tokens[2], 3);
  // printf("idk");
  // 	fflush(stdout);
  // printf("%s", idk);
  for (int i = 0; i < 10; i += 2) {
    printf("inside for");
    fflush(stdout);
    char currentDir = tokens[2][i];
    printf("idk");
    fflush(stdout);
    printf("%c\n", currentDir);
    fflush(stdout);
    if (currentDir <= 'Z' && currentDir >= 'A') {
      printf("%c\n", currentDir);
    } else { // Add else-if to check if file name for import_file
      printf("Directory path invalid\n");
      return;
    }
  }
  // int currentIndex = 0;
  // for (int i = 0; i < strnlen(names, 8); i++) {
  //   int entryIndex = 3;
  //   char currentEntry = currentDrive->block[currentIndex][entryIndex];
  //   while (entryIndex < 11 && currentEntry != names[i]) {
  //     char currentEntry = currentDrive->block[currentIndex][entryIndex];
  //   }
  //   if (currentEntry !=) {
  //   }
  // }

  // use the directory's bitmap to determine which entries are valid
  // print out the one character names of the valid entries

  // int dirIndex = 0;
  // int entryIndex = 3;

  // char currentEntry = currentDrive->block[dirIndex][entryIndex];
  // while(entryIndex = )
}

Drive *open_file(char **tokens) {
  // close the TFS-file currently in use, if any
  if (currentFile != -1) {
    close(currentFile);
    currentFile = -1;
    printf("inside if\n");
    fflush(stdout);
  }
  // open an existing TFS-disk file, fails if file DNE
  currentFile = open(tokens[1], O_RDWR);
  printf("%s", tokens[1]);
  fflush(stdout);
  if (currentFile == -1) {
    printf("Error, file invalid.\n");
    fflush(stdout);
    return currentDrive;
  }
  // make sure size of file is valid
  struct stat myInode;
  int ret = stat(tokens[1], &myInode);
  int fileSize = myInode.st_size;
  // TODO: check size when size is properly set for files
  // if (fileSize == 256) {
  // TODO: read the file into a Disk struct
  currentDrive = newDrive();
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      unsigned char b[1];
      read(currentFile, b, 1);
      printf("%c\n", b[0]);
      fflush(stdout);
      currentDrive->block[i][j] = b[0];
    }
  }
  // } else {
  //   printf("Error, file size is invalid.\n");
  // }
  return currentDrive;
}

// TODO: add this command to main. make sure if u change value both in thingy
// AND file, it will change properly. idk.
void changeIndex(char character, int blockIndex, int byteIndex) {
  currentDrive->block[blockIndex][byteIndex] = character;
}

Drive *create(char **tokens) {
  // close the TFS-file currently in use, if any
  if (currentFile != -1)
    close(currentFile);

  // if file exists, display error
  currentFile = open(tokens[1], O_RDONLY);
  printf("%d", currentFile);
  fflush(stdout);
  if (currentFile != -1) {
    printf("File already exists.\n");
    fflush(stdout);
    close(currentFile);
    currentFile = -1;
    return currentDrive;
  }
  // close(currentFile);

  // Create new file with specified name
  currentFile = open(tokens[1], O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
  if (currentFile == -1) {
    printf("Failed to create new file.\n");
    fflush(stdout);
    return currentDrive;
  }

  // create empty disk in memory
  currentDrive = newDrive();
  printf("Created drive!\n");
  fflush(stdout);
  // save it to the open file

  // TODO: AKJSDFHGREFJCNMX
  // const unsigned char *buf = (char *) malloc(254);
  // unsigned char *buf2 = unsigned char[254]();
  unsigned char *ret = malloc(256);

  // printf("%s\n", buf2);
  // fflush(stdout);

  strncpy(ret, dump(currentDrive), 256);
  // errno;

  printf("%s\n", ret);
  fflush(stdout);

  printf("%s\n", dump(currentDrive));
  fflush(stdout);

  const int RETSIZE = 700;
  char *temp = malloc(RETSIZE);
  char *fileOutput = malloc(RETSIZE);
  for (int i = 0; i < 256; i++) {
    sprintf(temp, "%.1x", ret[i]);
    strncat(fileOutput, temp, RETSIZE);
    // strncat(fileOutput,ret[i],RETSIZE);
  }

  write(currentFile, fileOutput, RETSIZE);
  // write(currentFile, &buf, 254);
  // close(currentFile);

  // printf("%d", b);
  // fflush(stdout);
  return currentDrive;
}

int getBlock(char *pathToParse) {
  char **path = parse_command(pathToParse, "/");

  // CHECK IF PATH IS VALID!

  if (sizeof(path) > 8) { // TODO: this prob wont work
    printf("Path is out of range.");
    return -1;
  }

  int currNameIndex = 0;
  char *currentName = path[0];
  int currentBlock = 0;
  int currentByte = 3;

  // Loop through names in path
  // Last valid index should be name of new directory/file
  while (path[currNameIndex + 1] != NULL) {
    // Every pathname must have length of 1
    // And be valid uppercase letter
    if (strlen(currentName) > 1 || currentName[0] < 'A' ||
        currentName[0] > 'Z') {
      printf("Invalid path name.");
      return -1;
    }

    // Loop thru bytes 3-10 looking for name
    while (currentName[0] != currentDrive->block[currentBlock][currentByte]) {
      // If went through entire list without finding, display error
      if (currentByte > 10) {
        printf("Directory %c not found in path", currentName[0]);
        return -1;
      }
    }
    // If found, check block->[currentBlock][oneOfthelast4]
    // To find update currentBlock and repeat the process
    // int isEven = currentByte % 2;
    // if !isEven shift right by 4.
    // else mask =
    //
    // unsigned long bitmap = 0;
    // unsigned long mask = 1;
    int isEven = currentByte % 2;
    currentByte = currentByte / 2 + 10;
    if (isEven) {
      currentBlock = currentDrive->block[0][currentByte] / 10;
      // memcpy(&bitmap, d->block[0][currentByte], 4);
    } else {
      currentBlock = currentDrive->block[0][currentByte] % 10;
      // memcpy(&bitmap, d->block[0][currentByte], 8);
      // mask = mask >> 4;
    }
    // TODO: what if isn't used anymore?

    // currentBlock = bitmap & mask;
    currentByte = 3;

    // Return block number of parent block so we can put the dir name in there
    // and update shite
  }
}

void makeDirectory(char **tokens, Drive *d) {
  int blockIndex = getBlock(tokens[1]);
  if (blockIndex == -1)
    return;

  // Create a new directory in the TFS-disk.

  // TODO: potentially use isUsed for this and finding block for new dir

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