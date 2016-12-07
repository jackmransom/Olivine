#include <stdint.h>
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

const char PKMN_CHAR_TABLE[] = { //Incomplete
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
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

enum PKMN_INDEX {
  PKMN_00, PKMN_BULBASAUR, PKMN_IVYSAUR, PKMN_VENUSAUR,
  PKMN_CHARMANDER,PKMN_CHARMELEON, PKMN_CHARIZARD, PKMN_SQUIRTLE,
  PKMN_WARTORTLE, PKMN_BLASTOISE, PKMN_CATERPIE, PKMN_METAPOD,
  PKMN_BUTTERFREE, PKMN_WEEDLE, PKMN_KAKUNA, PKMN_BEEDRILL,
  PKMN_PIDGEY, PKMN_PIDGEOTTO, PKMN_PIDGEOT, PKMN_RATTATA,
  PKMN_RATICATE, PKMN_SPEAROW, PKMN_FEAROW,
  PKMN_EKANS, PKMN_ARBOK, PKMN_PIKACHU,
  PKMN_RAICHU, PKMN_SANDSHREW, PKMN_SANDSLASH, PKMN_NIDORAN_F,
  PKMN_NIDORINA, PKMN_NIDOQUEEN, PKMN_NIDORAN_M, PKMN_NIDORINO,
  PKMN_NIDOKING, PKMN_CLEFAIRY, PKMN_CLEFABLE, PKMN_VILPIX,
  PKMN_NINETAILS, PKMN_JIGGLYPUFF, PKMN_WIGGLYTUFF, PKMN_ZUBAT,
  PKMN_GOLBAT, PKMN_ODDISH, PKMN_GLOOM, PKMN_VILEPLUME,
  PKMN_PARAS,PKMN_PARASECT, PKMN_VENONAT, PKMN_VENOMOTH,
  PKMN_DIGLETT, PKMN_DUGTRIO, PKMN_MEOWTH, PKMN_PERSIAN,
  PKMN_PSYDUCK, PKMN_GOLDUCK, PKMN_MANKEY, PKMN_PRIMEAPE,
  PKMN_GROWLITHE, PKMN_ARCANINE, PKMN_POLIWAG, PKMN_POLIWHIRL,
  PKMN_POLIWRATH, PKMN_ABRA, PKMN_KADABRA, PKMN_ALAKAZAM,
  PKMN_MACHOP, PKMN_MACHOKE, PKMN_MACHAMP, PKMN_BELLSPROUT,
  PKMN_WEEPINBELL, PKMN_VICTREEBEL, PKMN_TENTACOOL, PKMN_TENTACRUEL,
  PKMN_GEODUDE, PKMN_GRAVELER, PKMN_GOLEM, PKMN_PONYTA,
  PKMN_RAPIDASH, PKMN_SLOWPOKE, PKMN_SLOWBRO, PKMN_MAGNEMITE,
  PKMN_MAGNETON, PKMN_FARFETCHD, PKMN_DODUO, PKMN_DODRIO,
  PKMN_SEEL, PKMN_DEWGONG, PKMN_GRIMER, PKMN_MUK,
  PKMN_SHELLDER, PKMN_CLOYSTER, PKMN_GASTLY, PKMN_HAUNTER,
  PKMN_GENGAR, PKMN_ONIX, PKMN_DROWZEE, PKMN_HYPNO,
  PKMN_KRABBY, PKMN_KINGLER, PKMN_VOLTORB, PKMN_ELECTRODE,
  PKMN_EXEGGCUTE, PKMN_EXEGGUTOR, PKMN_CUBONE, PKMN_MAROWAK,
  PKMN_HITMONLEE, PKMN_HITMONCHAN, PKMN_LICKITUNG, PKMN_KOFFING,
  PKMN_WEEZING, PKMN_RHYHORN, PKMN_RHYDON, PKMN_CHANSEY, PKMN_TANGELA,
  PKMN_KANGASKHAN, PKMN_HORSEA, PKMN_SEADRA, PKMN_GOLDEEN,
  PKMN_SEAKING, PKMN_STARYU, PKMN_STARMIE, PKMN_MR_MIME,
  PKMN_SCYTHER, PKMN_JYNX, PKMN_ELECTABUZZ, PKMN_MAGMAR,
  PKMN_PINSIR, PKMN_TAUROS, PKMN_MAGIKARP, PKMN_GYARADOS,
  PKMN_LAPRAS, PKMN_DITTO, PKMN_EEVEE, PKMN_VAPOREON,
  PKMN_JOLTEON, PKMN_FLAREON, PKMN_PORYGON, PKMN_OMANYTE,
  PKMN_OMASTAR, PKMN_KABUTO, PKMN_KABUTOPS, PKMN_AERODACTYL,
  PKMN_SNORLAX, PKMN_ARTICUNO, PKMN_ZAPDOS, PKMN_MOLTRES,
  PKMN_DRATINI, PKMN_DRAGONAIR, PKMN_DRAGONITE, PKMN_MEWTWO,
  PKMN_MEW, PKMN_CHIKORITA, PKMN_BAYLEEF, PKMN_MEGANIUM,
  PKMN_CYNDAQUIL, PKMN_QUILAVA, PKMN_TYPHLOSION, PKMN_TOTODILE,
  PKMN_CROCONAW, PKMN_FERILIGATR, PKMN_SENTRET, PKMN_FURRET,
  PKMN_HOOTHOOT, PKMN_NOCTOWL, PKMN_LEDYBA, PKMN_LEDIAN,
  PKMN_SPINARAK, PKMN_ARIADOS, PKMN_CROBAT, PKMN_CHINCHOU,
  PKMN_LANTURN, PKMN_PICHU, PKMN_CLEFFA, PKMN_IGGLYBUFF,
  PKMN_TOGEPI, PKMN_TOGETIC, PKMN_NATU, PKMN_XATU,
  PKMN_MAREEP, PKMN_FLAAFFY, PKMN_AMPHAROS, PKMN_BELLOSSOM,
  PKMN_MARILL, PKMN_AZUMARILL, PKMN_SUDOWOODO, PKMN_POLITOED,
  PKMN_HOPPIP, PKMN_SKIPLOOM, PKMN_JUMPLUFF,
  PKMN_AIPOM, PKMN_SUNKERN, PKMN_SUNFLORA,
  PKMN_YANMA, PKMN_WOOPER, PKMN_QUAGSIRE,
  PKMN_ESPEON, PKMN_UMBREON, PKMN_MURKROW,
  PKMN_SLOWKING, PKMN_MISDREAVUS, PKMN_UNOWN, PKMN_WOBBUFFET,
  PKMN_GIRAFARIG, PKMN_PINECO, PKMN_FORRETRESS, PKMN_DUNSPARCE,
  PKMN_GLIGAR, PKMN_STEELIX, PKMN_SNUBBULL, PKMN_GRANBULL,
  PKMN_QWILFISH, PKMN_SCIZOR, PKMN_SHUCKLE, PKMN_HERACROSS,
  PKMN_SNEASEL, PKMN_TEDDIURSA, PKMN_URSARING, PKMN_SLUGMA,
  PKMN_MAGCARGO, PKMN_SWINUB, PKMN_PILOSWINE, PKMN_CORSOLA,
  PKMN_REMORAID, PKMN_OCTILLERY, PKMN_DELIBIRD, PKMN_MANTINE,
  PKMN_SKARMORY, PKMN_HOUNDOUR, PKMN_HOUNDOOM, PKMN_KINGDRA,
  PKMN_PHANPY, PKMN_DONPHAN, PKMN_PORYGON2, PKMN_STANTLER,
  PKMN_SMEARGLE, PKMN_TYROGUE, PKMN_HITMONTOP, PKMN_SMOOCHUM,
  PKMN_ELEKID, PKMN_MAGBY, PKMN_MILTANK, PKMN_BLISSEY,
  PKMN_RAIKOU, PKMN_ENTEI, PKMN_SUICUNE, PKMN_LARVITAR,
  PKMN_PUPITAR, PKMN_TYRANITAR, PKMN_LUGIA, PKMN_HO_OH,
  PKMN_CELEBI, PKMN_FC, PKMN_FD, PKMN_FE, PKMN_FF,
};

struct PokemonSave {
  uint8_t *data;
  size_t size;
};

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
}__attribute__((packed));

struct Party
{
  uint8_t count;
  uint8_t species[7];
  struct Pokemon pokes[6];
  uint8_t trainerNames[6][11];
  uint8_t pokemonNames[6][11];
}__attribute__((packed));

void encodeString(char *in, uint8_t *out, size_t length);
void decodeString(uint8_t *in, char *out, size_t length);
void printChecksum(uint8_t *data);
uint16_t calculateCrystalChecksum(uint8_t *data, const size_t size);
void writeChecksums(uint8_t *data);
void loadData(const char *path, struct PokemonSave *pkmnData);
void saveDataToFile(const char *path, struct PokemonSave *poke);
void getCharacterName(uint8_t *data, char *name);
void setName(uint8_t *data, char*name);
