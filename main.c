#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool Guessed(char guess, char* letters) {
	for (int i = 0; i < strlen(letters); i++) {
		if (guess == letters[i]) {
			return true;
		}
	}
	return false;
}

int NumUnderScores(char* word) {
	int count = 0;
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] == 95) {
			count++;
		}
	}
	return count;
}

bool Contains(char* word, char letter) {
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] == letter) {
			return true;
		}
	}
	return false;
}

void UpdateCurrent(char* answer, char* current, char guess) {
	for (int i = 0; i < strlen(answer); i++) {
		if (answer[i] == guess) {
			current[i] = guess;
		}
	}
}

int main(int argc, char *argv[]) {
	char* answer;
	char* hint;
	char* current;
	char letters[26];
	char guess;
	int tries = 6;
	bool won = false;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s Word Hint\n", argv[0]);
		exit(-1);
	}
	for (int i = 0; i < 26; i++) {
		letters[i] = '_';
	}
	answer = argv[1];
	for (int j = 0; j < strlen(answer); j++) {
		if (answer[j] > 90 && answer[j] != 95) {
			answer[j] -= 32;
		}
		if (!((answer[j] > 64 && answer[j] < 91) || answer[j] == 95)) {
			fprintf(stdout, "Invalid word only letters and underscores are allowed.\n");
			exit(-2);
		}
	}
	hint = argv[2];
	current = malloc (strlen(answer));
	if (current == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(-1);
	}
	strcpy(current, answer);
	for (int k = 0; k < strlen(current) ; k++) {
		if (answer[k] == '_') {
			current[k] = ' ';
		} else {
			current[k] = '_';
		}
	}

	printf("%s\n", current);
	printf("Hint: %s\n", hint);
	printf("Letters: %s\n", letters);

	while ((guess = getchar()) != EOF) {
		if (guess != 10) {
			if (guess > 90 ) {
				guess -= 32;
			}
			if (guess < 65 || guess > 90) {
				fprintf(stdout, "Invalid character.\n");
			} else {
				if (Guessed(guess, letters)) {
					printf("Already guessed: %c\n", guess);
				} else {
					if (Contains(answer, guess)) {
						UpdateCurrent(answer, current, guess);
					} else {
						tries--;
					}
					if (NumUnderScores(current) == 0) {
						won = true;
					}
					letters[guess - 65] = guess;
				}
			}
			printf("%s\n", current);
			printf("Hint: %s\n", hint);
			printf("Misses left: %d\n", tries);
			printf("Letters: %s\n", letters);
			if (won) {
				fprintf(stdout, "You Win!\n");
				exit(0);
			}
			if (tries < 1) {
				fprintf(stdout, "You Lose...\n");
				exit(0);
			}
		}
	}
	free(current);
	exit(0);
}
