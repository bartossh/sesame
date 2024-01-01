# SESAME

Sesame is a simple CLI tool written in C for validating password security.

This software is still under development, keep your expectations low.


![Password Strength](https://imgs.xkcd.com/comics/password_strength.png)


## Disclaimer

This software aims to help you check your password strength by using message entropy calculation and checking the password against the pwned password database. It is not an omnipotent tool to secure your password. Use your judgment based on the information given back from this software. We take no responsibility for the way you use and interpret information produced by this software.

The password that you will pass as an input to this software is not stored or sent anywhere. The SHA1 hash is created and 5 first characters are added to the request sent `GET https://api.pwnedpasswords.com/range/{first 5 hash chars}`. The downloaded  data of the list of pawned password hashes are then used to check your password. The full hash is compared to find a matching hash from downloaded list of hashes. If hashes matches your password hash then the corresponding number is used to confirm to you how many times the given password has been pwned.

It is safe to provide the password as an input to this software.


## Modules

- [x] Entropy
- [x] Pwned Passwords
- [ ] NLP model


### Entropy

[Claude Shannon](https://en.wikipedia.org/wiki/Claude_Shannon) developed information entropy as a measure of the information content in a message, which is a measure of uncertainty reduced by the message. In so doing, he essentially invented the field of information theory.

Calculating the entropy of the password is a very reliable measure of its strength.

#### The illusion of Complexity

Complexity in passwords is a topic often shrouded in misconceptions. Many believe that simply tacking on a capital letter or a number at the end of a password elevates its security. However, this approach is akin to putting a lock on a paper door. At first glance, it presents the illusion of security, but upon closer examination, it offers minimal real-world protection.

Thanks to today's vast password libraries and powerful computers, brute-force attacks are within the reach of any homegrown hacker. You can check if your password has been pawned here: Pwned Passwords. Even if your password hasn't been pawned or is not in the library it can still be vulnerable to attack simply if it contains only known words or some letters are exchanged to numbers or other characters such, for example: s to 5, x to #, e to 3, g to 9.

#### The Flawed Logic of Human Created Complexity

When it comes to creating complex passwords, humans often fall into the trap of their own patterns. We are creatures of habit, drawn to sequences and familiar structures that make sense to us. This innate preference for patterns extends to how we create passwords, often leading to choices that are more predictable than we realize.

The best measurement of the complexity comes from the field of physics and is named the entropy.I am recommending to read Entropy Wiki page. This project focuses on the entropy that is part of information theory. In 1948, Bell Labs scientist Claude Shannon developed similar statistical concepts of measuring microscopic uncertainty and diversity to the problem of random losses of information in telecommunication signals. Upon John von Neumann's suggestion, Shannon named this entity of missing information in an analogous manner to its use in statistical mechanics as entropy and gave birth to the field of information theory. This description has been identified as a universal definition of entropy.


### Pwned Passwords

Full description here: [';--have i been pwned?](https://haveibeenpwned.com/API/v3#SearchingPwnedPasswordsByRange)

#### Pwned Passwords overview

Pwned Passwords are hundreds of millions of passwords which have previously been exposed in data breaches. The service is detailed in the launch blog post and most recently in this post about the FBI and NCA feeding data into the service. . The data is queryable online via the Pwned Passwords webpage, accessible via the API or downloadable as an entire corpus of data that can be queried offline. The Pwned Passwords API is freely accessible without the need for a subscription and API key.

Each password is stored as both a SHA-1 and an NTLM hash of a UTF-8 encoded password. The downloadable source data delimits the hash and the password count with a colon (:) and each line with a CRLF.

Searching by range
In order to protect the value of the source password being searched for, Pwned Passwords also implements a k-Anonymity model that allows a password to be searched for by partial hash. This allows the first 5 characters of either a SHA-1 or an NTLM hash (not case-sensitive) to be passed to the API:

```
GET https://api.pwnedpasswords.com/range/{first 5 hash chars}
```

When a password hash with the same first 5 characters is found in the Pwned Passwords repository, the API will respond with an HTTP 200 and include the suffix of every hash beginning with the specified prefix, followed by a count of how many times it appears in the data set. The API consumer can then search the results of the response for the presence of their source hash and if not found, the password does not exist in the data set. A sample SHA-1 response for the hash prefix "21BD1" would be as follows:

```
0018A45C4D1DEF81644B54AB7F969B88D65:1
00D4F6E8FA6EECAD2A3AA415EEC418D38EC:2
011053FD0102E94D6AE2F8B83D76FAF94F6:1
012A7CA357541F0AC487871FEEC1891C49C:2
0136E006E24E7D152139815FB0FC6A50B15:2
...
```

### NLP model

:construction:


## Build

:construction:


## Usage

Run in terminal:

```sh
./sesame yourStringPasswordToValidate
```

Or pipe the input:
```sh
echo -n administrator | ./sesame
```

Example response:

```sh
INFO: Password: [ administrator ] has 52 bits of Shannon entropy.

STRENGTH: +++++++++++++                   |<<< MAX

INFO: It will take 142808 years and 75 days to brute force your password with speed of 1000 guesses/second.

INFO: Password [ administrator ] is Pwned 32708 times.
```

