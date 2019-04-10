#include <stdio.h>

char rot_cipher(char letter, int key); //Used for encryption and decryption of rotation cipher with key.
char sub_encrypt(char letter, const char *key); //Used for encryption of substitution cipher with key.
char sub_decrypt(char letter, const char *key); //Used for decryption of substitution cipher with key.

int main() {
	int index = 0; //Used in each case to iterate through letters in input_string.
	char letter; //Will become each subsequent letter of input string in each case. 
	int key; //Amount shifted along in rotation cipher (encryption or decryption)
	//const char input_string[200] = {0}; //This becomes length limit to input.
	char output_string[200] = {0}; //This value is the limit to message length
	
	
	//const char input_string[] = "WE should ATTACK NOW"; //Temporary measure to input an example message.
	const char input_string[] = "NY GkcPMX JFfJZU DCN"; //Temporary measure to input an example sub coded message.
	//const char input_string[] = "ZH VKRXOG DwwDfN QRZ"; //Temporary measure to input example rot coded message.
	key = 3; //Temporary measure to input key for rotation cipher.
	const char sub_key[26] = "JBZXYWVKAEUMLDCTIHGFPONSRQ"; //Temporary measure. Reordered alphabet used to scramble substitution cipher messages.
	
	printf("Select option (1-6)\n1 for rotation cipher encryption.\n2 for decryption of rotation cipher given key.\n3 for substitution cipher encryption. \n4 for decryption of substitution cipher given key. \n5 for decryption of rotation cipher without key. \n6 for decryption of substitution cipher without key. \nResponse: ");
	//Above line prompts user for a choice of the 6 operations this program performs.
	int menu_response;
	scanf("%d", &menu_response); //User's response is recorded in variable 'menu_response'.
	switch(menu_response) {		//switch() only runs code under case corresponding to menu_response value.
		//const char message[] = "WE SHOULD ATTACK NOW"; //message ends up being wrong if defined here...?
		case 1: 
			//const char message[] = "WE SHOULD KILL CAESER";
			printf("For the moment the message is %s, and the key is %d.\n", input_string, key);
			//printf("Enter message (size limit 200 characters) to be encrypted: "); //Remember to change this prompt if size limit changed.
			//scanf("%[^\n]s", &input_string);
			//printf("%s\n", input_string);
			//printf("Enter number of places letters will be shifted along i.e. key (0<key<26): ");
			//scanf("%d", &key);
			index = 0; //index is counter to iterate through message letters in WHILE.
			letter = input_string[index]; //letter now becomes the first letter in message.
			while(letter) { //Implicitly means while (letter != 0). Because last char in any string is NULL, this will ENDWHILE at end of string.
				output_string[index] = rot_cipher(letter, key);
				index++;
				letter = input_string[index];
			}
			printf("Encrypted version: %s", output_string); //Just prints resultant string.
			break;
		case 2:
			printf("For the moment the coded message is %s, and the key is %d.\n", input_string, key);
			//char message[200]; //This value is the limit to message length.
			key = -key; //Since encryption and decryption of rotation cipher are only distinguished by whether key is added or subtracted,
						//same function can be used for decryption once key has been made negative.
			index = 0; //index is counter to iterate through message letters in WHILE. 
			letter = input_string[index]; //letter now becomes the first letter in message.
			while(letter) { //Implicitly means while (letter != 0). Because last char in any string is NULL, this will ENDWHILE at end of string.
				output_string[index] = rot_cipher(letter, key);
				index++;
				letter = input_string[index];
			}
			printf("Decrypted version: %s", output_string); //Just prints resultant string.		
			break;
		case 3: 
			//const char input_string[] = "WE SHOULD ATTACK NOW";
			//const char input_string[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			//const char input_string[] = "ABCDETUVWXYZ";
			//const char sub_key[] = "ZXYWVUTSRQPONMLKJIHGFEDCBA";
			//const char sub_key[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			
			printf("For the moment message is '%s' and key is '%s'.\n", input_string, sub_key);
			index = 0; //Counter to iterate through letters in message.
			letter = input_string[index]; //letter set to first character in message.
			while(letter) {
				output_string[index] = sub_encrypt(letter, sub_key);
				index++;
				letter = input_string[index];
			}
			printf("Encrypted version: %s\n", output_string); //Prints resultant string	
			break;
		case 4: 
			printf("For the moment coded message is '%s' and key is '%s'.\n", input_string, sub_key);
			index = 0; //Counter to iterate through letters in input_string.
			letter = input_string[index]; //letter set to first character in input_string.
			while(letter) {
				output_string[index] = sub_decrypt(letter, sub_key);
				index++;
				letter = input_string[index];
			}
			printf("Decrypted version: %s\n", output_string); //Prints resultant string.
			break;
		case 5: //call appropriate function.
			break;
		case 6: //call appropriate function.
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
