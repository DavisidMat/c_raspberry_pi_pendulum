#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#define ADC_CHANNEL 2
#define ADC_PIN (26 + ADC_CHANNEL)
#define ADC_V_REF 3.3
#define ADC_RESOLUTION (1 << 12)
#define ADC_CONVERSION_FACTOR (ADC_V_REF / (ADC_RESOLUTION - 1)) // Ranges from 0 - 4095

#define PWM_PIN_I 26
#define PWM_PIN_II 27
#define PICO_CLOCK_CYCLE 8 // Value in nanoseconds
#define PWM_FREQUENCY  (490) // In Hz

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
    This function is similar to scanf() and fgets() functions.
    The main difference is that when the user submit its input, the last character (newline character) is replaced by carriage return '\r'

    Alternatively when the latter functions do not work for establishing a serial communication with minicom,
    this custom function can be used to store the user input.

    DISCLAIMER!:
    To avoid a buffer overflow, the input_string shall be big enough.
    Moreover, if the user input exceeds the input_string length the function will be stranded in an infinite loop.

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
        // This statement stores the user input into the string until finding the carriage return character '\r'.
        
        int char_i = 0;
        char buffer_char = '\0';

        while ((buffer_char = getchar()) != '\r')
        {
            if (buffer_char == '\n') break; // Alternative case when the "Enter" button submits a newline character '\n'

            input_string[char_i] = buffer_char;
            char_i +=1;
        }
}

int main(){
    // Initializing I/O
    stdio_init_all();
    adc_init();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    gpio_init(16);
    gpio_set_dir(16, GPIO_IN);
    gpio_pull_up(16);

    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_CHANNEL);

    gpio_set_function(PWM_PIN_I, GPIO_FUNC_PWM);
    //gpio_set_function(PWM_PIN_II, GPIO_FUNC_PWM);
    
    int slice_num_I = pwm_gpio_to_slice_num(PWM_PIN_I);
    //int slice_num_II = pwm_gpio_to_slice_num(PWM_PIN_II);

    float PWM_PERIOD = ((1.0 / (float) PWM_FREQUENCY) * 1000.0 * 1000.0 * 1000.0); // 10^9 to obtain period in nanoseconds
    int PWM_WRAP_NUM = (PWM_PERIOD / (float) PICO_CLOCK_CYCLE);

    pwm_config config = pwm_get_default_config(); // To obtain a pwm_config struct profile

    sleep_ms(2000);
    printf("csr: %d, div: %d, top %d\n",config.csr, config.div, config.top);

    //  pwm_set_wrap(slice_num_I, PWM_WRAP_NUM);
    //pwm_set_wrap(slice_num_II, PWM_WRAP_NUM);

    //pwm_config_set_clkdiv_int(&config, 2048);
    pwm_config_set_clkdiv_int(&config, 255);
    pwm_config_set_wrap(&config, 61036);

    sleep_ms(2000);
    printf("csr: %d, div: %d, top %d\n",config.csr, config.div, config.top);
    pwm_init(slice_num_I, &config, true);

    pwm_set_gpio_level(PWM_PIN_I, 61036/2); // UWU

    //pwm_set_chan_level(slice_num_I, PWM_CHAN_A, 0);
    //pwm_set_chan_level(slice_num_II, PWM_CHAN_A, 0);

    //  pwm_set_enabled(slice_num_I, true);
    //pwm_set_enabled(slice_num_II, true);

    // Initializing Variables
    char input_string[100] = "";
    int switch_state = 0;
    int raw_ADC_val = 0;
    float analog_ADC_val = 0;
    int counter = 0;

    while(true){

        write_user_input(input_string);
        counter ++;
        printf("Test #%d: , your message was: %s\n", counter, input_string);


        if (strcmp(input_string, "on") == 0 || strcmp(input_string, "ON") == 0)
        {
            printf("The LED is ON!\n");
            gpio_put(25, true);
            sleep_ms(500);
        }
        else if (strcmp(input_string, "off") == 0 || strcmp(input_string, "OFF") == 0)
        {
            printf("The LED is OFF!\n");
            gpio_put(25, false);
            sleep_ms(500);
        }
        else if (strcmp(input_string, "val") == 0 || strcmp(input_string, "VAL") == 0)
        {
            raw_ADC_val = adc_read();
            printf("The raw ADC value is: %d\n", raw_ADC_val);
            analog_ADC_val = raw_ADC_val * ADC_CONVERSION_FACTOR;
            printf("The analog ADC value is: %f\n", analog_ADC_val);
        }
        else if (strcmp(input_string, "status") == 0)
        {
            switch_state = !gpio_get(16);
            printf("Switch status is: %d\n", switch_state);
            uint16_t min_position = 189500;
            uint16_t max_position = 380000;

            pwm_set_chan_level(slice_num_I, PWM_CHAN_A, min_position);
            //pwm_set_chan_level(slice_num_II, PWM_CHAN_A, min_position);
            printf("Servos to 0 degrees\n");
            sleep_ms(1000);

            pwm_set_chan_level(slice_num_I, PWM_CHAN_A, max_position);
            //pwm_set_chan_level(slice_num_II, PWM_CHAN_A, max_position);
            printf("Servos to 180 degrees\n");
            sleep_ms(1000);
        }
        else if (strcmp(input_string, "servo") == 0)
        {
            while ((switch_state = !gpio_get(16)) == 1)
            {
            raw_ADC_val = adc_read();
            printf("The raw ADC value is: %d\n", raw_ADC_val);
            analog_ADC_val = raw_ADC_val * ADC_CONVERSION_FACTOR;
            printf("The analog ADC value is: %f\n", analog_ADC_val);

            uint32_t duty_cycle_servo = ((float) raw_ADC_val / (float) ((1 << 12) - 1)) * (float) PWM_WRAP_NUM;
            float testt = ((float) raw_ADC_val / (float) ((1 << 12) - 1));
            int pwm_status = pwm_get_counter(slice_num_I);

            printf("Duty cycle value is: %d , %d uwu\n", duty_cycle_servo, pwm_status);
            pwm_set_gpio_level(PWM_PIN_I, duty_cycle_servo);
            // pwm_set_chan_level(slice_num_I, PWM_CHAN_A, duty_cycle_servo);
            //pwm_set_chan_level(slice_num_II, PWM_CHAN_A, duty_cycle_servo);
            sleep_ms(500);
            }
        }
        else
        {
            printf("Invalid option, try again!\n");
        }

    }
}