#include <stdio.h>
#include <ctype.h>

char rot_cipher(char letter, int key); //Used for encryption and decryption of rotation cipher with key.
char sub_encrypt(char letter, const char *key); //Used for encryption of substitution cipher with key.
char sub_decrypt(char letter, const char *key); //Used for decryption of substitution cipher with key.
int rot_attack(const char *message); //Returns key of rotation coded message.
int ASCII_to_num(const char *number_string, int length); //

int main() {
	int index = 0; //Used in each case to iterate through letters in input_string.
	char letter; //Will become each subsequent letter of input string in each case. 
	int key; //Amount shifted along in rotation cipher (encryption or decryption)
	int key_get;
	char sub_key_get;
	int useless;
	//const char input_string[200] = {0}; //This becomes length limit to input.
	char output_string[250] = {0}; //This value is the limit to message length
	char input_string[250] = {0};
	char sub_key[30] = {0};
	char lit_key[6] = {0};
	
	
	//const char input_string[] = "WE should ATTACK NOW"; //Temporary measure to input an example message.
	//const char input_string[] = "NY GkcPMX JFfJZU DCN"; //Temporary measure to input an example sub coded message.
	//const char input_string[] = "ZH VKRXOG DwwDfN QRZ"; //Temporary measure to input example rot coded message.
	//key = 12; //Temporary measure to input key for rotation cipher.
	//const char sub_key[] = "JBZXYWVKAEUMLDCTIHGFPONSRQ"; //Temporary measure. Reordered alphabet used to scramble substitution cipher messages.
	
	FILE *input_string_stream;
	input_string_stream = fopen("C:/Users/harry/Documents/Assignments/Assessment 1 ENGG1003/input_string5.txt", "r");
	if (input_string_stream == NULL)
		printf("Input string file does not exist.\n");
	int menu_response = fgetc(input_string_stream);	
	printf("You chose %c\n", menu_response);
	useless = fgetc(input_string_stream); //Method of changing position in file.
	switch(menu_response) {		//switch() only runs code under case corresponding to menu_response value.
		//const char message[] = "WE SHOULD ATTACK NOW"; //message ends up being wrong if defined here...?
		case '1': 
			//fseek(input_string_stream, long int 1, SEEK_CUR);
			
			
			//const char message[] = "WE SHOULD KILL CAESER";
		//	printf("The message is %s, and the key is %d.\n", input_string, key);
			//printf("Enter message (size limit 200 characters) to be encrypted: "); //Remember to change this prompt if size limit changed.
			//scanf("%[^\n]s", &input_string);
			//printf("%s\n", input_string);
			//printf("Enter number of places letters will be shifted along i.e. key (0<key<26): ");
			//scanf("%d", &key);
			index = 0; //index is counter to iterate through message letters in WHILE.
			//letter = input_string[index]; //letter now becomes the first letter in message.
			key_get = fgetc(input_string_stream); 
			while (isspace(key_get) == 0) {
				lit_key[index] = key_get;
				index++;
				key_get = fgetc(input_string_stream); 
			}
			key = ASCII_to_num(lit_key, index);
			//printf("Key is %s.\n", lit_key);
			//printf("Key is %d.\n", key);
			//useless = fgetc(input_string_stream);
			letter = fgetc(input_string_stream);
			index = 0;
			while(letter != EOF) { //Implicitly means while (letter != 0). Because last char in any string is NULL, this will ENDWHILE at end of string.
				output_string[index] = rot_cipher(letter, key);
				index++;
				//letter = input_string[index];
				letter = fgetc(input_string_stream);
			}
			printf("Encrypted version: %s", output_string); //Just prints resultant string.
			break;
		case '2':
		//	printf("The coded message is %s, and the key is %d.\n", input_string, key);
			//useless = fgetc(input_string_stream); //Method of changing position in file.
			index = 0;
			key_get = fgetc(input_string_stream); 
			while (isspace(key_get) == 0) {
				lit_key[index] = key_get;
				index++;
				key_get = fgetc(input_string_stream); 
			}
			key = ASCII_to_num(lit_key, index);
			//printf("Key is %s.\n", lit_key);
			//printf("Key is %d.\n", key);
			//useless = fgetc(input_string_stream);
			key = -key; //Since encryption and decryption of rotation cipher are only distinguished by whether key is added or subtracted,
						//same function can be used for decryption once key has been made negative.
			//useless = fgetc(input_string_stream); 
			index = 0; //index is counter to iterate through message letters in WHILE. 
			letter = fgetc(input_string_stream); //letter now becomes the first letter in message.
			while(letter != EOF) { //Implicitly means while (letter != 0). Because last char in any string is NULL, this will ENDWHILE at end of string.
				output_string[index] = rot_cipher(letter, key);
				index++;
				letter = fgetc(input_string_stream);
			}
			printf("Decrypted version: %s", output_string); //Just prints resultant string.		
			break;
		case '3': 
			//const char input_string[] = "WE SHOULD ATTACK NOW";
			//const char input_string[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			//const char input_string[] = "ABCDETUVWXYZ";
			//const char sub_key[] = "ZXYWVUTSRQPONMLKJIHGFEDCBA";
			//const char sub_key[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			sub_key_get = fgetc(input_string_stream);
			index = 0;
			while (isspace(sub_key_get) == 0) {
				sub_key[index] = sub_key_get;
				index++;
				sub_key_get = fgetc(input_string_stream);
			}
			
			
			index = 0; //Counter to iterate through letters in message.
			letter = fgetc(input_string_stream); //letter set to first character in message.
			while(letter != EOF) {
				output_string[index] = sub_encrypt(letter, sub_key);
				index++;
				letter = fgetc(input_string_stream);
			}
			printf("Encrypted version: %s\n", output_string); //Prints resultant string	
			break;
		case '4': 
			sub_key_get = fgetc(input_string_stream);
			index = 0;
			while (isspace(sub_key_get) == 0) {
				sub_key[index] = sub_key_get;
				index++;
				sub_key_get = fgetc(input_string_stream);
			}
			
			
			index = 0; //Counter to iterate through letters in message.
			letter = fgetc(input_string_stream); //letter set to first character in message.
			while(letter != EOF) {
				output_string[index] = sub_decrypt(letter, sub_key);
				index++;
				letter = fgetc(input_string_stream);
			}
			printf("Decrypted version: %s\n", output_string); //Prints resultant string.
			break;
		case '5':
			letter = fgetc(input_string_stream);
			index = 0;
			while (letter != EOF) {
				input_string[index] = letter;
				index++;
				letter = fgetc(input_string_stream);
			}
			key = rot_attack(input_string);
			//printf("The key is: %d", key);
			char decrypted_message[250];
			int counter = 0;
			char letter = 1;
			while (letter) {
				decrypted_message[counter] = rot_cipher(input_string[counter], -key);
				counter++;
			}
			printf("Decrypted version: %s\n", decrypted_message);
			break;
		case '6': //call appropriate function.
			break;
		default: 
			printf("Error: enter number between 1 and 6.");
	}
	//printf("You picked %d", menu_response); //Testing what user typed in.
	return 0;
}

/*I had a choice in how to implement this as a function. 
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
decryption, key is made negative before the function is run.*/
char rot_cipher(char letter, int key) { //'letter' is letter to be encrypted, 'key' is distance letters will shift along alphabet.
	if ((letter >= 97) && (letter <= 122))	// This if() converts all letters to uppercase.
		letter = letter - 32;
	else if ((letter < 65) || (letter > 90))	//This if() ensures that spaces and obscure symbols remain unchanged.
		return letter;
	char en_letter = ((letter - 65) + key + 2*26)%26 + 65; 
	//Above line shifts letter by key amount along alphabet, uses modulus to ensure
    //'rotation' back into alphabet, then converts back to CAPS ASCII. Also adds
	//26 to ensure term modulus affects is positive.
	return en_letter;
}

char sub_encrypt(char letter, const char *key) {
	if ((letter >= 97) && (letter <= 122))	// This if() converts all letters to uppercase.
		letter = letter - 32;
	else if ((letter < 65) || (letter > 90))	//This if() ensures that spaces and obscure symbols remain unchanged.
		return letter;
	int letter_index; //'letter_index' becomes int (0-25) representing letter's position in alphabet, e.g. 0 = A, 1 = B, etc..
	letter_index = (letter - 65); //This works becuase in ASCII A = 65, B = 66, etc..
	return key[letter_index]; //The letter in key holding the position 'letter' does in alphabet is returned.
}

char sub_decrypt(char letter, const char *key) {
	if ((letter >= 97) && (letter <= 122))	// This if() converts all letters to uppercase.
		letter = letter - 32;
	else if ((letter < 65) || (letter > 90))	//This if() ensures that spaces and obscure symbols remain unchanged.
		return letter;
	int index = 0; //Used as counter to iterate through checking each character in 'key' to find the letter matching 'letter'.
	char letter_in_key = key[0]; //letter_in_key becomes each character in key.
	while (letter_in_key) { //Will evaluate false when letter is null, i.e. at end of string.
		if (letter_in_key == letter)
			return (index + 65);
		index++;
		letter_in_key = key[index];
	}
}

int rot_attack(const char *message) {
	char converted_message[250];
	char d_word[150];
	char word[150];
	int i;
	for (i = 0; i < 150; i++) {
		word[i] = 0;
		d_word[i] = 0;
	}
	/*FILE *message_stream;
	message_stream = fopen("C:/Users/harry/Documents/Assignments/Assessment 1 ENGG1003/message.txt", "r");
	if (message_stream == NULL)
		printf("message file does not exist.\n");
	const char message[1000] = {0};
	int m_letter = 0;
	while (m_letter != EOF)
		dictionary[] */ 
	int Lev_final = 0;
	int key, key_final = 0;
	for (key = 0; key < 26; key++) { //Per key
		//fseek(dictionary_stream, 0, SEEK_SET);
		static int letter_index1 = 0;
		int Lev_key = 0, i = 0;
		char letter1 = 1, letter, letter_from_message = 1;
		while (letter1) {
			letter1 = rot_cipher(message[i], (-key));
			converted_message[i] = letter1;
			i++;
		}
		while(letter_from_message != 0) { //Per word in message
			int Lev_word = 0;
			//printf("letter: %d\n", letter_from_message);
			static char word_length = -1; //This fixes an offset by one error. Maybe its the first run through
			static char d_word_length = 0;
			int letter_index2 = 0;			
			//printf("letter_index1: %d\n", letter_index1);
			while((letter_from_message != ' ') && (letter_from_message != 0)) {
				//letter_from_message = fgetc(message_stream);
				letter_from_message = converted_message[letter_index1];
				//printf("letter from message early on: '%c'\n", letter_from_message);
				//if ((letter_from_message >= 97) && (letter_from_message <= 122)) //Don't need bc rot_cipher does it anyway.
					//letter_from_message = letter_from_message - 32;
				if (letter_from_message != ' ') // should replace with if a letter
					word[letter_index2] = letter_from_message;
					word_length++;
				letter_index1++;
				letter_index2++;
				if (letter_from_message == ' ')
					break;
				}
			//letter_index1++;
			letter_from_message = converted_message[letter_index1];
			//printf("%s", word);
			FILE *dictionary_stream;
			dictionary_stream = fopen("C:/Users/harry/Documents/Assignments/Assessment 1 ENGG1003/10000 words.txt", "r");
			if (dictionary_stream == NULL)
				printf("dictionary file does not exist.\n");
			char d_letter_from_dic = 0, d_letter;
			//printf("letter from dictionary: %d\n", d_letter_from_dic);
			while(d_letter_from_dic != EOF) {
				int d_letter_index = 0;
				//printf("d_letter_from_dic: %c\n", d_letter_from_dic);
				while(isspace(d_letter_from_dic) == 0) { //While its an actual letter rather than space, newline, etc.
					//printf("%c", d_letter_from_dic);
					if ((d_letter_from_dic >= 97) && (d_letter_from_dic <= 122))
						d_letter_from_dic = d_letter_from_dic - 32;
					//printf("current d_letter: %c\n", d_letter_from_dic);
					d_word[d_letter_index] = d_letter_from_dic;
					d_word_length++;
					//printf("d_word: %s\n", d_word);
					//printf("%c", d_word[d_letter_index]);
					//printf("%s\n", d_word);
					d_letter_from_dic = fgetc(dictionary_stream);
					d_letter_index++;
				}
				//printf("d_letter_from_dic: %d\n", d_letter_from_dic);
				//printf("Checking key of %d... word: %s, d_word: %s\n", key, word, d_word);
				if (isspace(d_letter_from_dic) == 0) //I don't know why this if() works but it does.
					d_letter_from_dic = fgetc(dictionary_stream);
				letter = 67;
				d_letter = 1; //There was a problem here, letter variebles reused when they were needed to control overarching loop. Now note distiction between d_letter and d_letter_from dic, and letter and letter_from_message.
				int letter_index = 0;
				//printf("word: %s, length: %d\nd_word: %s, length: %d\n", word, word_length, d_word, d_word_length);
				if (word_length == d_word_length) {
					static int Lev = 0;
					letter = word[letter_index];
					//printf("Checking if word is done: %d.\n", letter);
					while (letter) {
						d_letter = d_word[letter_index];
						//printf("word: %s, d_word: %s.\n", word, d_word);
						//printf("current d_letter: %c\n", d_letter);
						if (letter == d_letter)
							Lev++;
						letter_index++;	
						letter = word[letter_index];
					}
					if (Lev > Lev_word)
						Lev_word = Lev;
					Lev = 0;
					//printf("Checking key of %d... word: %s, d_word: %s. Lev: %d, Lev_word: %d, Lev_key: %d, Lev_final: %d, key_final: %d\n", key, word, d_word, Lev, Lev_word, Lev_key, Lev_final, key_final);
				}
				//printf("d_word resetting.\n");
				d_word_length = 0;
				for (i = 0; i < 150; i++) {
					d_word[i] = 0;
				}
				//printf("d_letter_from_dic: %c\n", d_letter_from_dic);
				d_letter_from_dic = fgetc(dictionary_stream);
				//printf("current d_letter: %c\n", d_letter_from_dic);
			}
			//printf("word and d_word resetting.\n");
			word_length = -1; //This fixes an offset by one error. Maybe its the first run through
			for (i = 0; i < 150; i++) {
				word[i] = 0;
				d_word[i] = 0;
			}
			Lev_key += Lev_word;
			Lev_word = 0;
		}
		//printf("poop\n");
		if (Lev_key > Lev_final) {
			Lev_final = Lev_key;
			key_final = key;
		}
		//printf("key_final: %d\n", key_final);
		Lev_key = 0;
		letter_index1 = 0;
		for (i = 0; i < 250; i++) {
			converted_message[i] = 0;
		}
	}
	return key_final;
}

int ASCII_to_num(const char *number_string, int length) {
	int index = length;
	int number = 0;
	while (index > 1) {
		int i, multiplier = 10;
		for (i = 1; i < (index-1); i++)
			multiplier = 10*multiplier;
		//printf("multiplier: %d, to be added: %d\n", multiplier, (number_string[(length - index)]-48));
		number += (number_string[(length - index)] - 48)*multiplier;
		index--;
	}
	number += (number_string[(length - index)] - 48);
	return number;
}




