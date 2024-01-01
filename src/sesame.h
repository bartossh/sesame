#ifndef SESAME_H
#define SESAME_H

/// se_shannon calculates Shannon information entropy of given character string.
///
/// str - nullable string of characters.
unsigned long 
se_shannon(const unsigned char *str);

/// se_bruteForceDays calculates theoertical number of days required to brute force the password.
///
/// bits - number of entropy bits.
unsigned long long 
se_bruteForceDays(const unsigned long bits);

///se_yearsAndDays returns string in format "%llu years %llu days" from days.
///
///days - number of days.
char *
se_yearsAndDays(unsigned long long days);

/// se_getPwned crates a SHA-1 hash from given string and sends makes a request with first five characters 
/// to not expose the string. It receives the suffixes of SHA-1 hashes with number of exposures of the string
/// saved in the database. It compares the concatenated prefix and suffix with string hash calculating the 
/// number of occurrences.
///
/// str - string password to be validated.
unsigned long long se_getPwned(const unsigned char *str);

#endif
