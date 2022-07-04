#include <cs50.h>
#include <stdio.h>

// function to calculate sum of each digits
int sum_of_digits(int n)
{
    int sum = 0;
    // if digit >= 10
    while (n / 10 >= 1)
    {
        // split the digit and sum them
        int digit = n % 10;
        sum += digit;
        n /= 10;
    }
    // if digit < 10, straight away sum
    sum += n;
    return sum;
}

// Luhn's algorithm
int sum_of_mutiplication_of_every_other_digit(long n)
{
    int sum = 0;
    while (n > 0)
    {
        // get current last digit and multiply 2
        int digit = n % 10 * 2;

        // get sum of digits
        int digit_sum = sum_of_digits(digit);
        {
            // add it to total
            sum += digit_sum;
        }

        // divide n by 100 so that modulus 10 will skip a digit
        n /= 100;
    }
    return sum;
}

int sum_of_every_other_digit(long n)
{
    int sum = 0;
    while (n > 0)
    {
        // get current last digit and add to sum
        sum += n % 10;

        // divide n by 100 so that the next modulus 10 will skip the next digit
        n /= 100;
    }
    return sum;
}

// function to check if card is valid
void check_card(int sum, long num)
{
    bool valid = false;

    // if checksum is valid (Luhn's algorithm)
    if (sum % 10 == 0)
    {
        // assign n to an additional variable
        long number = num;

        // get card number length
        int length = 0;
        while (num > 0)
        {
            num /= 10;
            length++;
        }

        // get first 2 digits of card number
        while (number / 10 >= 10)
        {
            number /= 10;
        }
        int first_two_digits = number;

        // check is it AMEX
        if (length == 15)
        {
            if (first_two_digits == 34 || first_two_digits == 37)
            {
                valid = true;
                printf("%s\n", "AMEX");
            }
        }
        // check is it MASTERCARD
        else if (length == 16)
        {
            if (first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 || first_two_digits == 54 || first_two_digits == 55)
            {
                valid = true;
                printf("%s\n", "MASTERCARD");
            }
        }

        // get first digit of card number
        int first_digit = first_two_digits / 10;

        // check is it VISA
        if (first_digit == 4)
        {
            if (length == 13 || length == 16)
            {
                valid = true;
                printf("%s\n", "VISA");
            }
        }
    }
    
    // if card is not AMEX, VISA, MASTERCARD
    if (valid == false)
    {
        printf("%s\n", "INVALID");
    }
}

int main(void)
{
    // get card number from user
    long card_number = get_long("Number: ");

    // calculate checksum (Luhn's algorithm)
    int checksum = sum_of_mutiplication_of_every_other_digit(card_number / 10) + sum_of_every_other_digit(card_number);

    check_card(checksum, card_number);
}