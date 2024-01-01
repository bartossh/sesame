# SESAME

Sesame is a simple CLI tool written in C for validating password security.

This software is not ready yet.

![Password Strength](https://imgs.xkcd.com/comics/password_strength.png)


## Modules

- [x] Entropy
- [ ] Pwned Passwords
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


#### Usage

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


### Pwned Passwords

:construction:


### NLP model

:construction:


## Usage

:construction:

