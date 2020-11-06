#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */

    //Edited by MoRommy on 03/11/2020 at 10:42 PM
    nr >>= i;
    res = nr % 2;

    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */

    //Edited by MoRommy on 03/11/2020 at 11:19 PM
    int c = 1;
    for(int j = 1; j <= i; j++) {
        c *= 2;
    }
    res = c ^ nr;

    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    //Edited by MoRommy on 05/11/2020 at 03:18 PM

    int c = 1;
    for(int j = 1; j <= i; j++) {
        c *= 2;
    }
    res = c | nr;

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    int c = 1;
    for(int j = 1; j <= i; j++) {
        c *= 2;
    }
    res = ~c & n;

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */
	
	//edited by MoRommy on 02/11/2020 at 6:04 PM
	res = nand_gate(nand_gate(a, b), nand_gate(a, b));
	
    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

	//edited by MoRommy on 02/11/2020 at 6:08 PM
	res = nand_gate(a, a);
	
    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */

	//edited by MoRommy on 02/11/2020 at 6:09 PM
	res = nand_gate(not_gate(a), not_gate(b));
	
    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */
	
	//edited by MoRommy on 02/11/2020 at 6:13 PM
	res = nand_gate(nand_gate(a, nand_gate(a,b)), nand_gate(b, nand_gate(a, b)));
	
    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

	//edited by MoRommy on 02/11/2020 at 7:13 PM
	uint8_t sum = 0;
	sum = or_gate(
		and_gate(not_gate(a), xor_gate(b, c)),
		and_gate(a, or_gate(and_gate(b, c), and_gate(not_gate(b), not_gate(c))))
	);
	// sum = !a!bc + !ab!c + abc + a!b!c = !a(xor_gate(b, c) + a(bc + !b!c)
	
	uint8_t carry = 0;
	carry = or_gate(
		and_gate(a, or_gate(b, c)),
		and_gate(b, c)
	);
	// carry = ab + bc + ac = a(b + c) + bc

	sum = sum << 1;
	res = sum + carry;
	// 0 bit = carry bit
	// 1 bit = sum bit
    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */

    
    
    return res;
}
