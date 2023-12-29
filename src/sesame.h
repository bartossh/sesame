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

/// SE_bruteForceDays calculates theoertical number of days required to brute force the password.
///
/// bits - number of entropy bits.
unsigned long long SE_bruteForceDays(unsigned long bits);

///SE_yearsAndDays returns string in format "%llu years %llu days" from days.
///
///days - number of days.
char *SE_yearsAndDays(unsigned long long days);

#endif
