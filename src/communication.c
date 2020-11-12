#include "communication.h"
#include "util_comm.h"

#include <stdio.h>
#include <string.h>

/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */

    send_squanch('R' - 64);
    send_squanch('I' - 64);
    send_squanch('C' - 64);
    send_squanch('K' - 64);
}

void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    uint8_t character;
    for (int i = 1; i <= 5; i++) {
        character = recv_squanch();
        fprintf(stdout, "%c", character + 64);
    }

}

void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */
    uint8_t c;
    for (int i = 1; i <= 10; i++) {
        c = recv_squanch();
        send_squanch(c);
        send_squanch(c);
    }  

}

/* Task 2 - Waiting for the Message */

void send_custom_message(char message[])
{
    uint8_t length = strlen(message);
    send_squanch(length << 2);

    for (int i = 0; i < length; i++) {
        send_squanch(message[i] - 64);
    }
}

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */

    send_custom_message("HELLOTHERE");
}

uint8_t pow2(uint8_t n)
{
    /*
    // if (n < 0) return 1 / pow2(-n);
    * this returns a double type and we have got uint8_t
    */
    if (n == 0) return 1;
    else return 2 * pow2(n - 1);
}

uint8_t decodeLength(uint8_t length)
{
    uint8_t lengthDecoded = 0;
    length = length >> 2;
    for (int i = 0; i < 4; i++) {
        if (length % 2)
            lengthDecoded += pow2(i);
        length = length >> 1;
    }
    return lengthDecoded;
}

void printEachDecodedCharacter(uint8_t lengthDecoded)
{
    uint8_t character;
    for (int i = 0; i < lengthDecoded; i++) {
        character = recv_squanch();
        fprintf(stdout, "%c", character + 64);
    }
}

void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    uint8_t length = recv_squanch();
    uint8_t lengthDecoded = decodeLength(length);
    fprintf(stdout, "%d", lengthDecoded);
    printEachDecodedCharacter(lengthDecoded);
}

void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */

    uint8_t length = recv_squanch();
    uint8_t lengthDecoded = decodeLength(length);
    uint8_t character;
    for (int i = 0; i < lengthDecoded; i++) {
        character = recv_squanch();
    }

    if (character == 'P' - 64) {
        send_custom_message("PICKLERICK");
    }
    else {
        send_custom_message("VINDICATORS");
    }

}

/* Task 3 - In the Zone */

uint8_t activate_bit(uint8_t nr, uint8_t i)
{
    uint8_t res = 1ull << i | nr;
    
    return res;
}

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */

    uint8_t message = 0;

    for (int i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            if(c2 % 2)
                message = activate_bit(message, i);
            c2 = c2 >> 1;
        }
        else {
            if (c1 % 2)
                message = activate_bit(message, i);
            c1 = c1 >> 1;
        }
    }

    send_squanch(message);
}

uint8_t get_bit(uint8_t nr, uint8_t i)
{
    uint8_t res = -1;

    nr = nr >> i;
    res = nr % 2;

    return res;
}

uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */

    uint8_t string = 0;

    for (int i = 7; i >= 1; i -= 2) {
        if (get_bit(c, i))
            string += 1;
        string = string << 1;
    }

    for (int i = 6; i >= 0; i -= 2) {
        if (get_bit(c, i))
            string += 1;
        if (i)
            string = string << 1;
    }
    res = string;
    return res;
}
