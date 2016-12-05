#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//Save data offsets - http://bulbapedia.bulbagarden.net/wiki/Save_data_structure_in_Generation_II
#define PKMN_GSC_OPTIONS  0x2000
#define PKMN_GSC_TRAINER_ID  0x2009
#define PKMN_GSC_TRAINER_NAME  0x200B
#define PKMN_GSC_MOM_NAME  0x2013  //Unused
#define PKMN_GSC_RIVAL_NAME  0x2021
#define PKMN_GSC_RED_NAME  0x201C //Unused
#define PKMN_GSC_BLUE_NAME  0x2013 //Unused
#define PKMN_GSC_DAYLIGHT_SAVINGS  0x2037
#define PKMN_GSC_TIME_PLAYED  0x2054
#define PMKN_GSC_JOHTO_BADGES  0x23E5
#define PKMN_GSC_TM_POCKET  0x23E7
#define PKMN_GSC_ITEM_POCKET_ITEM_LIST  0x2420
#define PKMN_GSC_KEY_ITEM_POCKET_ITEM_LIST  0x244A
#define PKMN_GSC_BALL_POCKET_ITEM_LIST  0x2465
#define PKMN_GSC_PC_ITEM_LIST  0x247F
#define PKMN_C_CURR_PC_BOX_NO  0x2700
#define PKMN_C_JP_PC_BOX_NAMES  0x26E5
#define PKMN_C_TEAM_POKEMON_LIST  0x2865
#define PKMN_C_JP_TEAM_POKEMON_LIST  0x281A
#define PKMN_C_POKEDEX_OWNED  0x2A27
#define PKMN_C_POKEDEX_SEEN  0x2A47
#define PKMN_C_GENDER  0x3E3D
#define PKMN_C_JP_PLAYER_GENDER  0x8000

#define PKMN_C_PRIMARY_PART_START  0x2009
#define PKMN_C_PRIMARY_PART_END  0x2B82
#define PKMN_C_JP_PRIMARY_PART_END  0x2B3A

#define PKMN_C_SECONDARY_PART_START  0x1209
#define PKMN_C_SECONDARY_PART_END  0x1D82
#define PKMN_C_JP_SECONDARY_PART_END  0x7D3A
#define PKMN_C_JP_SECONDARY_PART_END  0x7D3A

#define PKMN_C_PART_LENGTH  0xB79
#define PKMN_C_JP_PART_LENGTH  0xB31

#define PKMN_C_CHECKSUM_1  0x2D0D
#define PKMN_C_CHECKSUM_2  0x1F0D
#define PKMN_C_JP_CHECKSUM_2  0x7F0D

#define PKMN_C_PLAYER_GENDER_MALE  0x0
#define PKMN_C_PLAYER_GENDER_FEMALE  0x1

const char PKMN_CHAR_TABLE[] = { //Incomplete
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'A', 'B',
  'C', 'D', 'E', 'F', 'G',
  'H', 'I', 'J', 'K', 'L',
  'M', 'N', 'O', 'P', 'Q',
  'R', 'S', 'T', 'U', 'V',
  'W', 'X', 'Y', 'Z', '(',
  ')', ':', ';', '[', ']',
  'a', 'b', 'c', 'd', 'e',
  'f', 'g', 'h', 'i', 'j',
  'k', 'l', 'm', 'n', 'o',
  'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y',
  'z', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f'
};

struct PokemonData {
  uint8_t *data;
  size_t size;
};

void printChecksums(uint8_t *data)
{
  uint16_t sum = (data[PKMN_C_CHECKSUM_1] << 8 ) | data[PKMN_C_CHECKSUM_1+1];
  printf("0x%X\n", sum);
  sum = (data[PKMN_C_CHECKSUM_2] << 8) | data[PKMN_C_CHECKSUM_2+1];
  printf("0x%X\n", sum);
}

void writeChecksums(uint8_t *data)
{
  uint16_t sum = 0;
  for(size_t i = PKMN_C_PRIMARY_PART_START; i < PKMN_C_PRIMARY_PART_START+PKMN_C_PART_LENGTH; ++i)
  {
    sum += data[i];
  }

  data[PKMN_C_CHECKSUM_1] = sum & 0xFF;
  data[PKMN_C_CHECKSUM_1+1] = sum >> 8;

  sum = 0;
  for(size_t i = PKMN_C_SECONDARY_PART_START; i<PKMN_C_SECONDARY_PART_START+PKMN_C_PART_LENGTH; ++i)
  {
    sum += data[i];
  }

  data[PKMN_C_CHECKSUM_2] = sum & 0xFF;
  data[PKMN_C_CHECKSUM_2+1] = sum >> 8;
}

void loadData(const char *path, struct PokemonData *pkmnData)
{
  FILE *f = fopen(path, "rb");
  if(f)
  {
    fseek(f, 0, SEEK_END);
    pkmnData->size = ftell(f);
    rewind(f);
    pkmnData->data = malloc(pkmnData->size);
    fread(pkmnData->data, pkmnData->size, 1, f);
    fclose(f);
  }
}

void saveDataToFile(const char *path, struct PokemonData *poke)
{
  memcpy(poke->data+PKMN_C_SECONDARY_PART_START,
      poke->data+PKMN_C_PRIMARY_PART_START, PKMN_C_PART_LENGTH);
  writeChecksums(poke->data);
  FILE *f = fopen(path, "wb");
  fwrite(poke->data, poke->size, 1, f);
  fclose(f);

}

void foo(uint8_t *data)
{
  int firstPoke = PKMN_C_TEAM_POKEMON_LIST+8;
  data[PKMN_C_TEAM_POKEMON_LIST+1] = 0xFB;
  data[firstPoke] = 0xFB;
  //int attackOffset = firstPoke + 0x26;
  int maxHPOffset = firstPoke + 0x24;
  data[maxHPOffset+1] = 69; //nice
  data[PKMN_C_GENDER] = PKMN_C_PLAYER_GENDER_MALE;
}

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    return 1;
  }
  const char *path = argv[1];
  struct PokemonData poke;
  loadData(path, &poke);
  printChecksums(poke.data);
  foo(poke.data);
  saveDataToFile(path, &poke);
  printChecksums(poke.data);
  free(poke.data);
  return 0;
}

