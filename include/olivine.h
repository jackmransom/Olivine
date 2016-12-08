#pragma once
#include <stdint.h>
#include <stddef.h>
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

#define PKMN_GSC_STR_TERMINATOR 0x50

#define PKMN_GSC_TRAINER_ID_MAX 65536
#define PKMN_GSC_PARTY_LIST_SIZE 428

struct PokemonSave {
  uint8_t *data;
  size_t size;
};

#pragma pack(1)
struct Pokemon
{
  uint8_t species;
  uint8_t item;
  uint8_t moves[4];
  uint16_t ot;
  uint8_t exp[3];
  uint16_t hpEV;
  uint16_t atkEV;
  uint16_t defEV;
  uint16_t speedEV;
  uint16_t specialEV;
  uint16_t ivs;
  uint8_t movePP[4];
  uint8_t friendship;
  uint8_t pokerus;
  uint16_t caught;
  uint8_t level;
  uint8_t status;
  uint8_t unused;
  uint16_t currHP;
  uint16_t maxHP;
  uint16_t attack;
  uint16_t defense;
  uint16_t speed;
  uint16_t specialAtk;
  uint16_t specialDef;
};

struct Party
{
  uint8_t count;
  uint8_t species[7];
  struct Pokemon pokes[6];
  uint8_t trainerNames[6][11];
  uint8_t pokemonNames[6][11];
};
#pragma pack()

void encodeString(const char *in, uint8_t *out, size_t length);
void decodeString(uint8_t *in, char *out, size_t length);

void printChecksum(uint8_t *data);
void writeChecksums(uint8_t *data);

void loadData(const char *path, struct PokemonSave *pkmnData);
void saveDataToFile(const char *path, struct Party *party, struct PokemonSave *poke);

void getCharacterName(uint8_t *data, char *name);
void setName(uint8_t *data, const char *name);
void getName(uint8_t *data, char *name);

uint16_t getTrainerID(struct Pokemon poke);

uint8_t calculateHPIV(uint8_t atkIV, uint8_t defIV, uint8_t speedIV, uint8_t specialIV);
