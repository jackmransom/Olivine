#ifndef _MSC_VER
#include <arpa/inet.h>
#else
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "olivine.h"

const char PKMN_CHAR_TABLE[] = { //Incomplete
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  '\0', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'A', 'B',
  'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
  'W', 'X', 'Y', 'Z', '(', ')', ':', ';', '[', ']',
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f'
};

void encodeString(const char *in, uint8_t *out, size_t length)
{
  size_t i= 0;
  while(i < length)
  {
    for(size_t j = 0x80; j < 0xFF; ++j)
    {
      if(in[i] == PKMN_CHAR_TABLE[j])
      {
        out[i++] = j;
      }
    }
  }
}

void decodeString(uint8_t *in, char *out, size_t length)
{
  size_t i;
  for(i = 0; i < length; ++i)
  {
    out[i] = PKMN_CHAR_TABLE[in[i]];
  }
  out[i+1] = '\0';
}

void printChecksum(uint8_t *data)
{
  uint16_t sum = (data[PKMN_C_CHECKSUM_1] << 8 ) | data[PKMN_C_CHECKSUM_1+1];
  printf("Checksum: 0x%X\n", sum);
}

static uint16_t calculateCrystalChecksum(uint8_t *data, const size_t size)
{
  uint16_t res = 0;
  for(size_t i = 0; i < size; ++i)
  {
    res += data[i];
  }
  return res;
}

void writeChecksums(uint8_t *data)
{
  *((uint16_t *) &data[PKMN_C_CHECKSUM_1]) = calculateCrystalChecksum(data+PKMN_C_PRIMARY_PART_START, PKMN_C_PART_LENGTH);
  *((uint16_t *) &data[PKMN_C_CHECKSUM_2]) = calculateCrystalChecksum(data+PKMN_C_SECONDARY_PART_START, PKMN_C_PART_LENGTH);
}

struct Party getParty(uint8_t *data)
{
  struct Party res;
  memcpy(&res, data+PKMN_C_TEAM_POKEMON_LIST, PKMN_GSC_PARTY_LIST_SIZE);
  for(size_t i = 0; i < res.count; ++i)
  {
    res.pokes[i].ot = ntohs(res.pokes[i].ot);
    res.pokes[i].ivs = ntohs(res.pokes[i].ivs);
    res.pokes[i].hpEV = ntohs(res.pokes[i].hpEV);
    res.pokes[i].atkEV = ntohs(res.pokes[i].atkEV);
    res.pokes[i].defEV = ntohs(res.pokes[i].defEV);
    res.pokes[i].speedEV = ntohs(res.pokes[i].speedEV);
    res.pokes[i].specialEV = ntohs(res.pokes[i].specialEV);
  }
  return res;
}

void getIVs(uint8_t *res, struct Pokemon *poke)
{
  uint16_t ivs = poke->ivs;
  res[0] = ivs >>12;
  res[1] = (ivs & 0xF00) >> 8;
  res[2] = (ivs & 0xF0) >> 4;
  res[3] = ivs & 0xF;
}

bool isPokemonShiny(struct Pokemon *poke)
{
  uint8_t ivs[4] = {0};
  getIVs(ivs, poke);
  uint8_t atkIV = ivs[0];
  uint8_t defIV = ivs[1];
  uint8_t speedIV = ivs[2];
  uint8_t specialIV = ivs[3];
  if(atkIV == 2 || atkIV == 3 || atkIV == 6 ||
      atkIV == 7 || atkIV == 10 || atkIV == 11 || atkIV == 14 || atkIV == 15)
  {
    return defIV == 10 && speedIV == 10 && specialIV == 10;
  } else {
    return false;
  }
}

void setShiny(struct Pokemon *poke)
{
  uint8_t ivs[4] = {0};
  getIVs(ivs, poke);
  uint8_t atkIV = ivs[0];
  uint8_t defIV = 10;
  uint8_t speedIV = 10;
  uint8_t specialIV = 10;

  if(atkIV != 2 || atkIV != 3 || atkIV != 6 ||
      atkIV != 7 || atkIV != 10 || atkIV != 11 || atkIV != 14 || atkIV != 15)
  {
    atkIV = 15;
  }
  uint16_t newIVs = atkIV << 12 | defIV << 8 | speedIV << 4 | specialIV;
  poke->ivs = newIVs;
}

void loadData(const char *path, struct PokemonSave *pkmnData)
{
  FILE *f = fopen(path, "rb");
  if(f)
  {
    fseek(f, 0, SEEK_END);
    pkmnData->size = ftell(f);
    rewind(f);
    pkmnData->data = malloc(pkmnData->size);
    fread(pkmnData->data, pkmnData->size, 1, f);
#ifdef _MSC_VER
    //TODO: Remove winsock dependency
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
#endif
    fclose(f);
  }
}

void savePartyData(struct Party *party, struct PokemonSave *poke)
{
  for(size_t i = 0; i < party->count; ++i)
  {
    party->pokes[i].ot = htons(party->pokes[i].ot);
    party->pokes[i].ivs = htons(party->pokes[i].ivs);
    party->pokes[i].hpEV = htons(party->pokes[i].hpEV);
    party->pokes[i].atkEV = htons(party->pokes[i].atkEV);
    party->pokes[i].defEV = htons(party->pokes[i].defEV);
    party->pokes[i].speedEV = htons(party->pokes[i].speedEV);
    party->pokes[i].specialEV = htons(party->pokes[i].specialEV);
  }
  memcpy(poke->data+PKMN_C_TEAM_POKEMON_LIST, party, PKMN_GSC_PARTY_LIST_SIZE);
}

void saveDataToFile(const char *path, struct Party *party, struct PokemonSave *poke)
{
  savePartyData(party, poke);
  memcpy(poke->data+PKMN_C_SECONDARY_PART_START, poke->data+PKMN_C_PRIMARY_PART_START, PKMN_C_PART_LENGTH);
  writeChecksums(poke->data);
  FILE *f = fopen(path, "wb");
  if(f)
  {
    fwrite(poke->data, poke->size, 1, f);
    fclose(f);
  }
}

void getCharacterName(uint8_t *data, char *name)
{
  size_t i = 0;
  size_t j = PKMN_GSC_TRAINER_NAME;
  uint8_t *nameIn = malloc(sizeof(uint8_t)*11);
  while(data[j] != PKMN_GSC_STR_TERMINATOR)
  {
    nameIn[i++] = data[j++];
  }
  decodeString(nameIn, name, i);
  free(nameIn);
}

uint16_t getStatValue(uint16_t base, uint8_t level, uint16_t iv, uint16_t ev, char isHP)
{
  uint16_t stat = floor((sqrt(ev-1)+1)/4);
  uint16_t res = (((base + iv)* 2+ stat)*level/100)+ (isHP ? level + 10: 5);
  return res;
}

void setName(uint8_t *data, const char *name)
{
  uint8_t nameBuf[11];
  size_t len = strlen(name);
  memset(nameBuf, PKMN_GSC_STR_TERMINATOR, 11);
  encodeString(name, nameBuf, len);
  memcpy(data, &nameBuf, 11);
}

void getName(uint8_t *data, char *name)
{
  decodeString(data, name, 11);
}

void setPartyPokemon(struct Party *party, struct Pokemon pokemon, int pos, char *trainer, char *nickname)
{
  if(party->species[pos-1]== 0xFF)
  {
    party->count++;
    party->species[pos] = 0xFF;
  }
  printf("Setting Pokemon: %d(%s) in Position: %d\n", pokemon.species, nickname,pos);
  party->species[pos-1] = pokemon.species;
  memcpy(&party->pokes[pos-1], &pokemon, sizeof(pokemon));
  setName(party->trainerNames[pos-1], trainer);
  setName(party->pokemonNames[pos-1], nickname);
}

uint8_t calculateHPIV(struct Pokemon *poke)
{
  uint8_t ivs[4] = {0};
  getIVs(ivs, poke);
  uint8_t atkIV = ivs[0];
  uint8_t defIV = ivs[1];
  uint8_t speedIV = ivs[2];
  uint8_t specialIV = ivs[3];
  return (((atkIV % 2 == 1 ? 8 : 0) << 3) | ((defIV % 2 == 1 ? 4 : 0) << 2) | ((speedIV % 2 == 1 ? 2 : 0) << 1) | (specialIV % 2 == 1 ? 1 : 0)) >> 3;

}
/*
struct Pokemon bar(uint8_t species, uint16_t ivs, uint16_t hpEV, uint16_t atkEV, uint16_t defEV, uint16_t speedEV, uint16_t specialEV)
{
  struct Pokemon res = {0};

  uint32_t exp = 420;
  res.level = 9;

  res.species = species;
  res.item = 0x52; //King's Rock

  res.moves[0] = 0x01;
  res.moves[1] = 0x5E;

  res.exp[0] = (exp >> 16) & 0xFF;
  res.exp[1] = (exp >> 8) & 0xFF;
  res.exp[2] = exp & 0xFF;

  res.movePP[0] = 4;
  res.movePP[1] = 20;

  uint8_t hpIV = calculateHPIV(atkIV, defIV, speedIV, specialIV);
  uint16_t hp = getStatValue(100, res.level, hpIV, hpEV, 1);

  res.attack = htons(getStatValue(100, res.level, atkIV, atkEV, 0));
  res.defense = htons(getStatValue(100, res.level, defIV, defEV, 0));
  res.speed = htons(getStatValue(100, res.level, speedIV, speedEV, 0));
  res.specialAtk = htons(getStatValue(100, res.level, specialIV, specialEV, 0));
  res.specialDef = htons(getStatValue(100, res.level, specialIV, specialEV, 0));

  return res;
}*/
