# Dungeon Cube Caesar 🎲

A C program that implements a two‑player game where a random five‑letter word is generated and two dice are rolled each round. Players reveal letters based on dice rolls, and the first to uncover the entire word loses and triggers a Caesar cipher encryption of the word.

## 📖 Description

- Word Generation: Randomly generates a 5‑letter lowercase word each playthrough.
- Dice Rolls: Prompts for two dice sides (e.g., 3x3, 2 x 5, allowing flexible whitespace).
- Gameplay Loop:
  1. Player 1 (you) enters a name (2–8 characters).
  2. Rolls two dice each round and advances through the word by the sum of the two dice, revealing letters.
  3. Player 2 ("Bob") rolls the same dice and advances similarly.
  4. Continues until one player's index reaches the word length (5).
- Endgame: The loser’s revealed word is encrypted with a Caesar cipher using a shift equal to the player’s total roll sum mod 26. The encrypted word is displayed, followed by a "Game Ended!" message.

## 🚀 Prerequisites

- GCC or any C compiler (supports C99)
- Make utility

## 🛠️ Installation & Build

From the project root:
```bash
# Compile the program
make
```
This builds the executable `p1_achu4_203` in the same directory.

To clean build artifacts:
```bash
make clean
```

## ▶️ How to Use

### Interactive Mode

Run the program and follow on‑screen prompts:
```bash
./p1_achu4_203
```

### Using Sample Input

You can redirect a prepared input file:
```bash
./p1_achu4_203 < input.txt
```
where `input.txt` contains:
```bash
<seed>         # integer seed for randomness
<name>         # player name (2–8 chars)
<sides>        # dice sides in NxM format
```

## 📜 Sample

```bash
Enter seed for RNG: 123
Enter your name [2–8 characters]: Joe
Enter the sides of the 2 dice [NxM]: 3x3
Welcome Joe!
    Joe word is: ab
    Bob word is: cd
    ...
Joe lost the game!
Their encrypted word is qwert
Game Ended!
```
