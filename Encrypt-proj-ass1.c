//HEADER-----------------------------------------------------------------------------------------------------------------
/*
ENGG1003 project 1 by Henry Wheeler.
This program requires a 10 000 word dictionary in the same file directory, and takes an input in the form of a
.txt file formatted as following: Beginning with a number 1 through 5 to choose the desired operation, then a
newline character, then if necessary a key (e.g. "3" to rotate through 3 letters to the right in alphabet, or
"JBZXYWVKAEUMLDCTIHGFPONSRQ" to substite A for J and so on), followed by a newline. Anything after this in the
.txt file will be treated as the message to be operated on.

Operation 1: The message is encrypted with a rotation cipher with a user specified key.
Operation 2: The message previously encrypted via rotation cipher is decrypted with the key specified by the user.
Operation 3: The message is encrypted with a substitution cipher in accordance with a user specified key.
Operation 4: The message previously encrypted with a substituion cipher is decrypted with the key specified by the user.
Operation 5: The message previously encrypted with a rotation cipher is decrypted without need of key from user.
*/

//LIBRARY DECLARATIONS---------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <ctype.h>

//FUNCTION PROTOTYPES----------------------------------------------------------------------------------------------------
char rot_cipher(char letter, int key); //Used for encryption and decryption of rotation cipher with key. Acts on one letter.
char sub_encrypt(char letter, const char *key); //Used for encryption of substitution cipher with key. Acts on one letter.
char sub_decrypt(char letter, const char *key); //Used for decryption of substitution cipher with key. Acts on one letter.
int rot_attack(const char *message); //Returns key of rotation coded message. Has a message size limit of 9500.
int ASCII_to_num(const char *number_string, int length); //Converts a string array made up of ASCII numbers into a base 10 integer.

int main() {

//VARIABLE DECLARATIONS---------------------------------------------------------------------------------------------------	
	int index = 0; //Used in each case to iterate through letters in input_string.
	char letter; //Will become each subsequent letter of input string in each case. 
	int key; //Amount shifted along in rotation cipher (encryption or decryption)
	int key_get; //Variable to store each digit of rotation key if it is larger than 9.
	char sub_key_get; //Variable to store each letter in substitution cipher key at a time.
	int useless; //File data is occasionally stored to this variable just to allow the file stream to move on. In debugging allows someone to check what is being skipped over.
	char output_string[9500] = {0}; //Value in [] is the limit to message length. Stores message after operation.
	char input_string[9500] = {0}; //Value in [] is the limit to message length. Stores message before operation.
	char sub_key[30] = {0}; //Stores user inputted key for substitution cipher.
	char lit_key[6] = {0}; //Stores all digits of rotation cipher key in case larger than 9. Value in [] is limit to digits in key.
	
//MAIN BODY---------------------------------------------------------------------------------------------------------------
	FILE *input_string_stream; //Will be stream from user's .txt file.
	input_string_stream = fopen("input_string.txt", "r"); //Opens user's .txt file for reading.
	if (input_string_stream == NULL) //This if() verifies that the file has been found.
		printf("Input string file does not exist.\n");
	int menu_response = fgetc(input_string_stream);	//First character in file assumed to be choice of operation.
	printf("You chose operation %c\n", menu_response); //Confirmation of choice.
	useless = fgetc(input_string_stream); //Method of changing position in file.
	switch(menu_response) {		//switch() only runs code under case corresponding to menu_response value. Makes the correct operation happen.
		case '1': 
			//printf("The message is %s, and the key is %d.\n", input_string, key); //To test if key and message have been received correctly.
			index = 0; //index is counter to iterate through message letters in WHILE.
			key_get = fgetc(input_string_stream); //key_get becomes first character in key.
			while (isspace(key_get) == 0) { //Loops so long as a whitespace character like \n is not reached.
				lit_key[index] = key_get; //Charcters in key are collected.
				index++; 
				key_get = fgetc(input_string_stream); //key_get becomes next character in key to test loop condition and prepare for next loop.
			}
			key = ASCII_to_num(lit_key, index); //Converts string of ASCII number characters into an integer.
			letter = fgetc(input_string_stream); //letter becomes first character in message.
			index = 0; //index reset to zero so it can be reused as counter.
			while(letter != EOF) { //Because fgetc() returns EOF or -1 at end of file, this will ENDWHILE at end of message.
				output_string[index] = rot_cipher(letter, key); //Encrypts each subsequent character in message.
				index++;
				letter = fgetc(input_string_stream); //letter becomes next character in message to test loop condition and prepare for next loop.
			}
			printf("Encrypted version: %s", output_string); //Just prints resultant string after operation.
			break; //To ensure only one case runs.
		case '2':
			//printf("The coded message is %s, and the key is %d.\n", input_string, key); //To test if key and message have been received correctly.
			index = 0; //index is counter to iterate through message letters in WHILE.
			key_get = fgetc(input_string_stream); //key_get becomes first character in key.
			while (isspace(key_get) == 0) { //Loops so long as a whitespace character like \n is not reached.
				lit_key[index] = key_get; //Charcters in key are collected.
				index++;
				key_get = fgetc(input_string_stream); //key_get becomes next character in key to test loop condition and prepare for next loop.
			}
			key = ASCII_to_num(lit_key, index); //Converts string of ASCII number characters into an integer.
			key = -key; //Since encryption and decryption of rotation cipher are only distinguished by whether key is added or subtracted,
						//same function can be used for decryption once key has been made negative.
			//useless = fgetc(input_string_stream); 
			index = 0; //index is counter to iterate through message letters in WHILE. 
			letter = fgetc(input_string_stream); //letter now becomes the first letter in message.
			while(letter != EOF) { //Because fgetc() returns EOF or -1 at end of file, this will ENDWHILE at end of message.
				output_string[index] = rot_cipher(letter, key); //Decrypts each subsequent character in message.
				index++;
				letter = fgetc(input_string_stream); //letter becomes next character in message to test loop condition and prepare for next loop.
			}
			printf("Decrypted version: %s", output_string); //Just prints resultant string after operation.	
			break; //To ensure only one case runs.
		case '3': 
			sub_key_get = fgetc(input_string_stream); //key_get becomes first character in key.
			index = 0; //index is counter to iterate through message letters in WHILE.
			while (isspace(sub_key_get) == 0) { //Loops so long as a whitespace character like \n is not reached.
				sub_key[index] = sub_key_get; //Charcters in key are collected.
				index++;
				sub_key_get = fgetc(input_string_stream); //key_get becomes next character in key to test loop condition and prepare for next loop.
			}
			index = 0; //Counter to iterate through letters in message.
			letter = fgetc(input_string_stream); //letter set to first character in message.
			while(letter != EOF) { //Because fgetc() returns EOF or -1 at end of file, this will ENDWHILE at end of message.
				output_string[index] = sub_encrypt(letter, sub_key); //Encrypts each subsequent character in message.
				index++;
				letter = fgetc(input_string_stream); //letter becomes next character in message to test loop condition and prepare for next loop.
			}
			printf("Encrypted version: %s\n", output_string); //Just prints resultant string after operation.
			break; //To ensure only one case runs.
		case '4': 
			sub_key_get = fgetc(input_string_stream); //key_get becomes first character in key.
			index = 0; //index is counter to iterate through message letters in WHILE.
			while (isspace(sub_key_get) == 0) { //Loops so long as a whitespace character like \n is not reached.
				sub_key[index] = sub_key_get; //Charcters in key are collected.
				index++;
				sub_key_get = fgetc(input_string_stream); //key_get becomes next character in key to test loop condition and prepare for next loop.
			}
			index = 0; //Counter to iterate through letters in message.
			letter = fgetc(input_string_stream); //letter set to first character in message.
			while(letter != EOF) { //Because fgetc() returns EOF or -1 at end of file, this will ENDWHILE at end of message.
				output_string[index] = sub_decrypt(letter, sub_key); //Decrypts each subsequent character in message.
				index++;
				letter = fgetc(input_string_stream); //letter becomes next character in message to test loop condition and prepare for next loop.
			}
			printf("Decrypted version: %s\n", output_string); //Just prints resultant string after operation.
			break; //To ensure only one case runs.
		case '5':
			//No key to be collected.
			letter = fgetc(input_string_stream); //letter set to first character in message.
			index = 0; //index is counter to iterate through message letters in WHILE.
			while (letter != EOF) { //Because fgetc() returns EOF or -1 at end of file, this will ENDWHILE at end of message.
				input_string[index] = letter; //Collects each subsequent message character to be passed to rot_attack() function.
				index++;
				letter = fgetc(input_string_stream); //letter becomes next character in message to test loop condition and prepare for next loop.
			}
			key = rot_attack(input_string); //Figures out key of rotation cipher based on message.
			printf("The key is: %d\n", key); //Prints key found for clarification.
			int counter = 0; //Iterates through characters in output string to decrypt.
			char letter = 1; //Initialised to 1 so that WHILE runs first time.
			while (letter) { //Implicitly means while(letter != 0), meaning this will loop until end of string because end of sting is NULL and unused spaces are 0.
				output_string[counter] = rot_cipher(input_string[counter], -key); //Decrypts each subsequent character in message.
				counter++;
				letter = input_string[counter]; //letter becomes next character in message to test loop condition and prepare for next loop.
			}
			printf("Decrypted version: %s\n", output_string); //Just prints resultant string after operation.
			break; //To ensure only one case runs.
		case '6': //Section 6 was not completed.
			printf("Section 6 was not completed.\n");
		default: 
			printf("Error: enter number between 1 and 5.");
	}
	//printf("You picked %d", menu_response); //Testing what user typed in.
	return 0;
}

//FUNCTION DEFINITIONS--------------------------------------------------------------------------------------------------------------------

/*
I had a choice in how to implement this as a function. 
Arrays (e.g. strings) cannot be returned by functions, 
so the function must either handle printing the result 
on its own, or the function must act only on one element
(letter) of the message array at a time. (Pointers could
solve this but they would be the most difficult route)

I initially chose the former, but changed my mind because
in order to work with file I/O I will need to read from a 
file, process and write to a new file one letter at a time.

This function is used to both encrypt and decrypt rotation
ciphers, since the two operations are so similar. For 
decryption, key is made negative before the function is run.
*/
char rot_cipher(char letter, int key) { //'letter' is letter to be encrypted, 'key' is distance letters will shift along alphabet.
	if ((letter >= 97) && (letter <= 122))	// This if() converts all letters to uppercase.
		letter = letter - 32;
	if ((letter < 65) || (letter > 90))	//This if() ensures that spaces and non-letter symbols remain unchanged.
		return letter;
	char en_letter = ((letter - 65) + key + 2*26)%26 + 65; 
	//Above line shifts letter by key amount along alphabet, uses modulus to ensure
    //'rotation' back into alphabet, then converts back to CAPS ASCII. Also adds a
	//multiple of 26 to ensure term modulus affects is positive. 
	return en_letter;
}

/*
This function encrypts text with a substitution cipher. The
key is the alphabet in its new order. For example, any "A" in
the text is replaced with the first letter in this new alphabet.
*/
char sub_encrypt(char letter, const char *key) {
	if ((letter >= 97) && (letter <= 122))	// This if() converts all letters to uppercase.
		letter = letter - 32;
	else if ((letter < 65) || (letter > 90))	//This if() ensures that spaces and obscure symbols remain unchanged.
		return letter;
	int letter_index; //'letter_index' becomes int (0-25) representing letter's position in alphabet, e.g. 0 = A, 1 = B, etc..
	letter_index = (letter - 65); //This works becuase in ASCII A = 65, B = 66, etc..
	return key[letter_index]; //The letter in key holding the position usually belonging to 'letter' in alphabet is returned.
}

/*
This function decrypts text that was previously encrypted with
a substitution cipher. Assumes key is in same format as described 
in above function.
*/
char sub_decrypt(char letter, const char *key) {
	if ((letter >= 97) && (letter <= 122)) // This if() converts all letters to uppercase.
		letter = letter - 32;
	else if ((letter < 65) || (letter > 90)) //This if() ensures that spaces and obscure symbols remain unchanged.
		return letter;
	int index = 0; //Used as counter to iterate through checking each character in 'key' to find the letter matching 'letter'.
	char letter_in_key = key[0]; //letter_in_key becomes each character in key.
	while (letter_in_key) { //Will evaluate false when letter is null, i.e. at end of string.
		if (letter_in_key == letter) //If matching letter is found, its position in key is used to return original letter.
			return (index + 65);
		index++;
		letter_in_key = key[index]; //letter_in_key becomes next character to test condition and set up for next loop.
	}
}

/*
This function takes a rotation encrypted message, tries each 
key, and returns the key that produces the most legible
message.
*/
int rot_attack(const char *message) {
	char converted_message[9500]; //Value in [] is the limit to message length. Stores message after operation.
	char d_word[150]; 
	char word[150]; //Used to store dictionary and message words respectively. Reasonable limit to word length of 150.
	int i; //Used to iterate through arrays and reset them to be empty (zeros).
	for (i = 0; i < 150; i++) { //Resetting arrays to be empty on each loop.
		word[i] = 0;
		d_word[i] = 0;
	}
	int Lev_final = 0; //Will be the measure of legibility of the most successful key.
	int key, key_final = 0; //key_final will store the best performing (most legible output) key.
	for (key = 0; key < 26; key++) { //Per key
		static int letter_index1 = 0; //Iterates through total letters in message dealt with in order to fill output string.
		int Lev_key = 0; //Will be the measure of how well each key performs (output legibility).
		int i = 0; //Iterates through letters in message to attempt decryption by each key.
		char letter1 = 1; //Becomes each subsequent letter in message to attempt decryption by each key.
		char letter; //Becomes each subsequent letter in each word of message to evaluate legibility.
		char letter_from_message = 1; //Becomes each letter in converted message so they can be sorted into individual words.
		while (message[i]) { //Runs until end of message[]
			letter1 = rot_cipher(message[i], (-key));
			converted_message[i] = letter1;
			i++;
		}
		int rep; //Counts the number of characters from message have been used.
		for (rep = 0; rep < 25; rep++) { //Limits the number of characters read from message, as not all are needed to find key accurately.
			if (letter_from_message == 0) //Ensures that process still stops if message is shorter than sample size.
				break;
			int Lev_word = 0; //Measure of legibility of each word.
			static char word_length = -1; //This fixes an offset by one error.
			static char d_word_length = 0; //Respective lengths of words from message and dictionary.
			int letter_index2 = 0; //Iterates through word arrays to fill them.
			while((letter_from_message != ' ') && (letter_from_message != 0)) { //Loop continues until the end of each word in converted message. 
				letter_from_message = converted_message[letter_index1]; //Becomes each subsequent converted message letter.
				if ((letter_from_message >= 65) && (letter_from_message <= 90)) //if(is a letter) to keep potential symbols out of word arrays.
					word[letter_index2] = letter_from_message; //Word array filled with letters.
					word_length++; //Length of word counted because sizeof(word) would give full size, used and unused.
				letter_index1++;
				letter_index2++;
				if (letter_from_message == ' ') //Ensures process moves on if end of word.
					break;
				}
			letter_from_message = converted_message[letter_index1]; //Moves on to next letter so next word does not begin with a ' '.
			FILE *dictionary_stream; //Declaring variable to be stream from dictionary.
			dictionary_stream = fopen("10000 words.txt", "r"); //Opening dictionary for reading.
			if (dictionary_stream == NULL) //Checking that dictionary was found.
				printf("dictionary file does not exist.\n");
			char d_letter_from_dic = 0; //Becomes each letter in dictionary and is used to test whether dictionary file is over.
			char d_letter; //Becomes each letter in each dictionary word for the purposes of comparing message and dictionary words letter by letter.
			while(d_letter_from_dic != EOF) { //Iterates through whole dictionary.
				int d_letter_index = 0; //Used to keep track of how far through each dictionary word it is. Resets here for next word.
				//printf("d_letter_from_dic: %c\n", d_letter_from_dic);
				while(isspace(d_letter_from_dic) == 0) { //While its an actual letter rather than space, newline, etc.
					if ((d_letter_from_dic >= 97) && (d_letter_from_dic <= 122)) //Converts to uppercase if necessary.
						d_letter_from_dic = d_letter_from_dic - 32;
					d_word[d_letter_index] = d_letter_from_dic; //d_word becomes word from dictionary.
					d_word_length++; //Length of d_word counted manually.
					d_letter_from_dic = fgetc(dictionary_stream); //next letter set up for testing loop and next repetition.
					d_letter_index++;
				}
				d_letter = 1; //There was previously a problem here, letter variebles reused when they were needed to control overarching loop. Now note distiction between d_letter and d_letter_from dic, and letter and letter_from_message.
				int letter_index = 0; //Used to call each letter in word and d_word.
				if (word_length == d_word_length) { //Only compares words if they are the same length as rotation cipher will never change length of word.
					static int Lev = 0; //Counts up how many letters match between word and d_word.
					letter = word[letter_index];
					while (letter) { //Loop continues until end of word.
						d_letter = d_word[letter_index];
						if (letter == d_letter) //Lev incremented if current letters match.
							Lev++;
						letter_index++;	//Moves on to next letters in each word.
						letter = word[letter_index]; //letter updated here so that the loop condition can be tested.
					}
					if (Lev > Lev_word) //The only important metric is what the highest value of Lev for a message word was, so that is stored in Lev_word.
						Lev_word = Lev;
					Lev = 0; //Lev reset each dictionary word.
				}
				d_word_length = 0; //d_word and its length reset.
				for (i = 0; i < 150; i++) {
					d_word[i] = 0;
				}
				d_letter_from_dic = fgetc(dictionary_stream); //To move on from the whitespace character between words in dictionary.
			}
			word_length = -1; //Message word length reset. -1 instead of 0 fixes an offset by one error. 
			for (i = 0; i < 150; i++) { //word and d_word reset after done with a message word.
				word[i] = 0;
				d_word[i] = 0;
			}
			Lev_key += Lev_word; //Lev_key tallies up all the scores of each message word with the dictionary to generate a score representing the legibility of the whole message with that key.
			Lev_word = 0; //Lev_word reset once score passed to Lev_key.
			fclose(dictionary_stream); //Stream must be closed to prevent eventual errors from buffering.
		}
		if (Lev_key > Lev_final) { //The highest Lev_key value becomes Lev_final, and whichever key produced it becomes the chosen key.
			Lev_final = Lev_key;
			key_final = key;
		}
		Lev_key = 0; //Lev_key reset after its score is passed onto Lev_final.
		letter_index1 = 0; //Reset to go back to the start of the message text.
		for (i = 0; i < 9500; i++) {
			converted_message[i] = 0; //Converted message reset so next key can be tried.
		}
	}
	return key_final; //Most legible key passed back to main()
}

/*
This function accounts for the possibility of a 2 or more digit number rotation
key in the input file. These numbers are strings or ASCII numbers in the text,
and therefore must be converted into actual integers before processing can be
done on them. This function does the same thing people do in their heads when
they read base 10 numbers.
*/
int ASCII_to_num(const char *number_string, int length) { //Length must be passed manually to function because sizeof() would not work.
	int index = length;
	int number = 0;
	while (index > 1) {
		int i, multiplier = 10;
		for (i = 1; i < (index-1); i++)
			multiplier = 10*multiplier; //Generating what each digit must be multiplied by e.g. 10, 100, 1000.
		number += (number_string[(length - index)] - 48)*multiplier; // -48 converts each digit from ASCII to integer.
		index--;
	}
	number += (number_string[(length - index)] - 48); //Result of each multiplication added up to final answer.
	return number;
}




