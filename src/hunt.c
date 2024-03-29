#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    uint8_t res = -1;
    nr = nr >> i;
    res = nr % 2;

    return res;
}

uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    uint64_t res = -1;
	res = ~(1ull << i) & nr;

    return res;
}

uint64_t activate_bit(uint64_t nr, uint8_t i)
{

    uint64_t res = 0xFF;
    res = 1ull << i | nr;

    return res;
}

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = -1;
    uint8_t i = 0, consecutive_bits_counter = 0;
    while (memory) {
    	if (get_bit(memory, 0)) {
    		consecutive_bits_counter++;
    	}
    	else {
    		consecutive_bits_counter = 0;
    	} 
    	memory = memory >> 1;
    	if (consecutive_bits_counter == 5) {
    		break;
    	}
    	i++;
    }

    for (uint8_t j = 63; j > 15; j--) {
    	memory = clear_bit(memory, j);
    }

    res = memory;
    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = -1;
	uint8_t i = 0, consecutive_bits_counter = 0;
    while (1) {
    	if (get_bit(memory, i)) {
    		consecutive_bits_counter++;
    	}
    	else {
    		consecutive_bits_counter = 0;
    	}
    	if (consecutive_bits_counter == 3) {
    		break;
    	}
    	i++;
    }

    i -= 3;
	for (uint8_t j = 63; j > i; j--) {
    	memory = clear_bit(memory, j);
    }

    for (int8_t j = i - 16; j >= 0; j--) {
    	memory = memory >> 1;
    }

    res = memory;
    return res;
}



uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = 0;

    for (uint8_t i = 0; i < 16; i++) {
    	if (get_bit(spell, i) != get_bit(key, i)) {
    		res = activate_bit(res, i);
    	}
    }

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1;

    uint32_t sword = 0;
    uint8_t active_bits_counter = 0;
    for (uint8_t i = 0; i < 16; i++) {
    	if(get_bit(enemy, i)) {
    		active_bits_counter++;
    	}
    }
    if (active_bits_counter % 2 == 0) {
    	sword += 9;
    	sword = sword << 28;
    	uint16_t difference = 1 - enemy;
    	for (uint8_t i = 0; i < 16; i++) {
    		if(get_bit(difference, i) == 1 && get_bit(enemy, i) == 1) {
    			sword = activate_bit(sword, i);
    		}
    	}
    }
    else {
    	sword += 6;
    	sword = sword << 28;
    	enemy = -enemy;
    	sword += enemy;
    }

    res = sword;
    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = -1;

    res = cocktail << 16;

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    if (map == -1) return 2;
    if (map ==  0) return 0;

    uint8_t active_bits_in_a_row = 0, 
    		max_counter = 0, 
    		min_counter = 4,
    		found_new_max = 0;

    for (uint8_t i = 0; i < 64; i++) {
    	if (get_bit(map, i)) {
    		active_bits_in_a_row++;
    		if (active_bits_in_a_row > max_counter) {
			    max_counter = active_bits_in_a_row;
			    found_new_max = 1;
			}
    	}
    	else {
    		if (max_counter < min_counter && found_new_max) {
			    min_counter = max_counter;
			}
    		active_bits_in_a_row = 0;
    		found_new_max = 0;
    	}
    }

    if (max_counter == min_counter && max_counter == 4) {
    	return 0;
    }
    if (max_counter == min_counter && max_counter == 2) {
    	return 1;
    }

    return 3;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = -1;

    uint8_t found_portal_location = 0,
    		found_candidate_location = 0,
    		i = 0;

    while (!found_portal_location) {
    	if (get_bit(map, i)) {
    		found_portal_location = i;
    		break;
    	}
    	i++;
    }
    i++;

    while (!found_candidate_location) {
    	if (get_bit(map, i)) {
    		found_candidate_location = i;
    	}
    	i++;
    }

    res = found_candidate_location - found_portal_location; 

    return res;
}
