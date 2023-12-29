#ifndef SESAME_H
#define SESAME_H

/// SESAME_check checks which modules are working.
///
/// Returns 0 if OK, or Error otherwise.
int SE_check(void);

/// SE_shannon calculates Shannon information entropy of given character string.
///
/// str - nullable string of characters.
unsigned long 
SE_shannon(unsigned char *str);

#endif
