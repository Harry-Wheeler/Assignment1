#include <stdio.h>

char rot_encrypt(char letter, int key); //limit of 200 character message, can be increased.

int main() {
	int index = 0; //Used in each case to iterate through letters in input_string.
	char letter; //Will become each subsequent letter of input string in each case.
	const char input_string[] = "WE SHOULD ATTACK NOW"; //Temporary measure to input an example message.
	//const char input_string[] = "ZH VKRXOG DWWDFN QRZ"; //Temporary measure to input example coded message.
	int key = 3; //Temporary measure to input key for rotation cipher.
	
	printf("Select option (1-6)\n1 for rotation encryption.\n2 for decryption of rotation cipher given key.\n3 for substitution encryption. \n4 for decryption of substitution given key. \n5 for decryption of rotation without key. \n6 for decryption of substitution without key. \nResponse: ");
	//Above line prompts use for a choice of the 6 operations this program performs.
	int menu_response;
	scanf("%d", &menu_response); //User's response is recorded in variable 'menu_response'.
	switch(menu_response) {		//switch() only runs code under case corresponding to menu_response value.
		//const char message[] = "WE SHOULD ATTACK NOW"; //message ends up being wrong if defined here...?
		case 1: 
			//const char message[] = "WE SHOULD KILL CAESER";
			printf("For the moment the message is %s, and the key is %d.\n", input_string, key);
			char en_message[200]; //This value is the limit to message length.
			index = 0; //index is counter to iterate through message letters in WHILE.
			//int key = 3;
			letter = input_string[index]; //letter now becomes the first letter in message.
			while(letter) { //Implicitly means while (letter != 0). Because last char in any string is NULL, this will ENDWHILE at end of string.
				en_message[index] = rot_encrypt(letter, key);
				index++;
				letter = input_string[index];
			}
			//Below just prints resultant string.
			index = 0;
			letter = en_message[index];
			while (letter) {
				printf("%c", letter);
				index++;
				letter = en_message[index];
			}
			break;
		case 2:
			printf("For the moment the coded message is %s, and the key is %d.\n", input_string, key);
			char message[200]; //This value is the limit to message length.
			key = -key; //Since encryption and decryption of rotation cipher are only distinguished by whether key is added or subtracted,
						//same function can be used for decryption once key has been made negative.
			index = 0; //index is counter to iterate through message letters in WHILE. 
			letter = input_string[index]; //letter now becomes the first letter in message.
			while(letter) { //Implicitly means while (letter != 0). Because last char in any string is NULL, this will ENDWHILE at end of string.
				message[index] = rot_encrypt(letter, key);
				index++;
				letter = input_string[index];
			}
			//Below just prints resultant string.
			index = 0;
			letter = message[index];
			while (letter) {
				printf("%c", letter);
				index++;
				letter = message[index];
			}			
			break;
		case 3: //call appropriate function.
		case 4: //call appropriate function.
		case 5: //call appropriate function.
		case 6: //call appropriate function.
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
char rot_encrypt(char letter, int key) { //'letter' is letter to be encrypted, 'key' is distance letters will shift along alphabet.
	
	if (letter == 32)			//This if() ensures that spaces remain unchanged.
		return 32;
	else {
		char en_letter = ((letter - 65) + key + 2*26)%26 + 65; 
		//Above line shifts letter by key amount along alphabet, uses modulus to ensure
	    //'rotation' back into alphabet, then converts back to CAPS ASCII. Also adds
		//26 to ensure term modulus affects is positive.
		return en_letter;
	}
}
