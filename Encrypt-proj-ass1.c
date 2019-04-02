#include <stdio.h>

void rot_encrypt(const char *message, int key); //limit of 200 character message, can be increased.

int main() {
	const char message[] = "WE SHOULD ATTACK NOW"; //Termporary measure to input an example message.
	printf("Select option (1-6)\n1 for rotation encryption.\n2 for decryption of rotation cipher given key.\n3 for substitution encryption. \n4 for decryption of substitution given key. \n5 for decryption of rotation without key. \n6 for decryption of substitution without key. \nResponse: ");
	int menu_response;
	scanf("%d", &menu_response);
	/*if (menu_response < 1 || menu_response > 6) { //This if() should be made unnecessary by default of switch
		//printf("Error: enter number between 1 and 6.");
		//At this point I would call the menu function again if it were a function.
	}*/
	switch(menu_response) {
		//const char message[] = "WE SHOULD ATTACK NOW"; //message is wrong if defined here.
		case 1: 
			//const char message[] = "WE SHOULD ATTACK NOW"; //Won't compile if defined here.
			printf("For the moment the message to be encrypted is defaulted to %s, but you can pick the encryption key (-26 < key < 26): ", message);
			int key;
			scanf("%d", &key);
			rot_encrypt(message, key);
			break;
		case 2: //call appropriate function.
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
	
I chose the former. Although my code will be
more convoluted and less reusable overall, the functions 
will be entirely self contained.*/
void rot_encrypt(const char *message, int key) { //message is original message to be encrypted, key is distance letters will shift along alphabet.
	char en_message[200]; //This value is the limit to message length.
	int index = 0; //index is counter to iterate through message letters in WHILE.
	char letter = message[index]; //letter now becomes the first letter in message.
	while (letter) { //Implicitly means while (letter != 0). Because last char in any string is null, this will ENDWHILE at end of string.
		if (letter == 32)			//This if() ensures that spaces remain unchanged.
			en_message[index] = 32;
		else
			en_message[index] = ((letter - 65) + key + 26)%26 + 65; /*Shifts letter by key amount along alphabet, uses modulus to ensure
		                                                         'rotation' back into alphabet, then converts back to CAPS ASCII. Also adds
																 26 to ensure term modulus affects is positive.*/
		index++;												
		letter = message[index];
	}
	printf("Encrypted version: %s", en_message);
}
