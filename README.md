# COMPUTERS PROGRAMMING
# Project 1
### Part 1 - Bits & Pieces

##### Task 1 - Bit by Bit
* get_bit(): For this task I shifted my number "i" times, and the 'i' bit became the less significant bit. Then, I would verify if the number was odd or even.
* flip_bit(): I created the number 1000..0 (with i zero's) and then I made XOR with the given number.
* activate_bit: I created the number 1000..0 (with i zero's) and then I made OR with the given number.
* clear_bit(): I created the number 1000..0 (with i zero's), negated all bits, and made AND with the given number.

##### Task 2 - One gate to rule them all
* nand_gate(): Implemented NAND on bits
* not_gate(): Implemented NOT with NAND
* or_gate(): Implemented OR with NAND
* xor_gate(): Implemented XOR with NAND

##### Task 3 - Just Carry the Bit
* full_adder(): Made Karnaugh diagram and minimized sum and carry functions, implemented them, and codified the result as SC (0 bit = carry bit, 1 bit = sum bit)
```sh
    sum = !a!bc + !ab!c + abc + a!b!c = !a(xor_gate(b, c)) + a(bc + !b!c)
    carry = ab + bc + ac = a(b + c) + bc
```
* ripple_carry_adder(): In order to implement this, I made a 'for' loop. If my sum bit was true and carry was zero or carry was true and sum was zero, I would activate, at every step, my "res" bit at that position. In that case, carry would get the zero value. This variable always traveled from loop to loop. In the end, if there was ANY overflow at the time of adding "a" and "b", then the result would be 0.


### Part 2 - Shut up Morty!

##### Task 1 - The beginning
* send_byte_message(): I  have just sent the characters encoded.
* recv_byte_message(): With a for loop I saved all the received chars in a variable, and then I printed them decoded.
* comm_byte(): With a for loop I saved all the received chars in a variable, and then I sent them two times.

##### Task 2 - Waiting for the Message
* send_message(): For this task I made a new function called send_custom_message() that receives a string, send its length, and then send each character encoded.
* recv_message(): I decoded the length, printed it, and then printed each encoded character.
* comm_message(): I received the length, decoded it, received all the chars, and took the last one. After that, I sent the messages depending on it.

##### Task 3 - In the Zone
* send_squanch2(): In order to implement this, I made a "for" loop and at every even step I activated the bit in my message if the c2 bit was true, and then I shifted left my c2 number 1 time. I did the same for odd steps, with c1.
* decode_squanch2(): I took the odd bits and added to my string, and then the even.

### Part 3 - Toss a coin to your Witcher

##### Task 1 - Axii
* find_spell(): I searched the position where my 5 consecutive bits are, shifting my number to left every time, and then I deleted the bits from the most significant bit to my finded position + 16 bits.
* find_key(): I searched the position where my 3 consecutive bits are, deleted every bit to the most significant, and then deleted every bit from my finded position + 16 to my least significant bit.
* I made XOR on bits.
##### Task 2 - Sword Play
* choose_sword(): I counted every true bit and if this number was even, I added to my sword value 9 (1001 on bits), shifted right with 28 bits, and calculate the ecuation for monster. I did the same thing for human, obviously with its values.
##### Task 3 - The Witcher Trials
* trial_of_the_grasses(): I found that my antibodies is my cocktail shifted 16 times to left.
* trial_of_forest_eyes(): If the forest was full of trees I returned 2, and if it was empty I returned 0. After that, I calculated min and max bites in a row. If those values were equal between them and equal with 4, I returned 0. I they were equal to 2, I returne 1. For other else, I returned 3.
* trial_of_dreams(): I found candidate and portal positions, and calculate the difference between them.
