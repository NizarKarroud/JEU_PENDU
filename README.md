# Markov Word Guesser

A small C program that builds a probabilistic Markov tree from a list of words and then tries to **guess a random word letter by letter** using frequency-based probabilities.

## 🧩 Description

The program creates a **Markov tree** where:
- Each node represents a letter.
- Each edge represents a transition between letters in the word list.
- Each node stores frequency and probability based on how often that letter follows the previous one.

After building the tree, the program:
1. Selects a random word from a predefined list.
2. Guesses each letter by traversing the tree in order of **most probable transitions**.
3. Prints whether each guess was correct or not.
4. Stops when the word is found or when all attempts are used.
