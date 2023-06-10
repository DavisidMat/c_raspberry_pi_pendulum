#include <stdio.h>
#include <string.h>

void clear_input_buffer()
{
    /*
    This functions clears the input buffer.
    */
    int buffer_char;
    while ((buffer_char = getchar()) != '\n' && buffer_char != EOF);
}

void format_input_string(char *input_string)
{
    /*
    This function formats the input string for displaying puporses.

    When fgets() is used to store the user input, by default it also includes the newline character (at the moment the user
    presses the enter button), causing a newline character display at the moment of displaying the stored value.
    To lead with this situation, this function checks if the input string contains a newline character '\n' and if its the case,
    that value in the memory address will be replaced by the null character '\o'.

    Additionally, this function also call the void function clear_input_buffer() cleaning the input buffer if data is present.
    */
    char *end_character = strchr(input_string, '\n'); // Checks if the newline character '\n' is present
    if (end_character == NULL)
    {
        clear_input_buffer();
    }
    else
    {
        *end_character = '\0';
    }
}

void write_user_input(char *input_string)
{
    /*
    This function does the same as the scanf() and fgets() functions.
    Alternatively when the latter funtions do not work for establishing a serial communication with minicom,
    this custom function can be used to store the user input.

    To avoid a buffer overflow, the input_string shall be big enough.

    -----------
    Parameters:
    char *input_string
        A pointer/list containing the pointer to which information is written.
    
    --------
    Returns:
    None
    */
   
    int i = 0;
        // This statement iterates and reinitializes the values of the char list.
        while (input_string[i] != '\0')
        {
            input_string[i] = '\0';
            i += 1;
        }
        // This statement stores the user input into the string until finding the newline character.
        
        int char_i = 0;
        char buffer_char = '\0';

        while ((buffer_char = getchar()) != '\n')
        {
            input_string[char_i] = buffer_char;
            char_i +=1;
        }
}

int main(){
    
    char input_string[30] = {};
    char buffer_char = '\0';

    int counter = 0;


    printf("Answer is 1 << 12, %d, %ld", 1<<12, sizeof(1<<12));

    while(1){

        write_user_input(input_string);
        //format_input_string(input_string);

        counter ++;
        printf("Test uwu: %d , your message was: %s\n", counter, input_string);

    }
}