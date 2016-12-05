#!/usr/bin/env python3
import sys

#Save data offsets - http://bulbapedia.bulbagarden.net/wiki/Save_data_structure_in_Generation_II
PKMN_GSC_OPTIONS = 0x2000
PKMN_GSC_TRAINER_ID = 0x2009
PKMN_GSC_TRAINER_NAME = 0x200B
PKMN_GSC_MOM_NAME = 0x2013  #Unused
PKMN_GSC_RIVAL_NAME = 0x2021
PKMN_GSC_RED_NAME = 0x201C #Unused
PKMN_GSC_BLUE_NAME = 0x2013 #Unused
PKMN_GSC_DAYLIGHT_SAVINGS = 0x2037
PKMN_GSC_TIME_PLAYED = 0x2054
PMKN_GSC_JOHTO_BADGES = 0x23E5
PKMN_GSC_TM_POCKET = 0x23E7
PKMN_GSC_ITEM_POCKET_ITEM_LIST = 0x2420
PKMN_GSC_KEY_ITEM_POCKET_ITEM_LIST = 0x244A
PKMN_GSC_BALL_POCKET_ITEM_LIST = 0x2465
PKMN_GSC_PC_ITEM_LIST = 0x247F
PKMN_C_CURR_PC_BOX_NO = 0x2700
PKMN_C_JP_PC_BOX_NAMES = 0x26E5
PKMN_C_TEAM_POKEMON_LIST = 0x2865
PKMN_C_JP_TEAM_POKEMON_LIST = 0x281A
PKMN_C_POKEDEX_OWNED = 0x2A27
PKMN_C_POKEDEX_SEEN = 0x2A47
PKMN_C_GENDER = 0x3E3D
PKMN_C_JP_PLAYER_GENDER = 0x8000

PKMN_C_PRIMARY_PART_START = 0x2009
PKMN_C_PRIMARY_PART_END = 0x2B82
PKMN_C_JP_PRIMARY_PART_END = 0x2B3A

PKMN_C_SECONDARY_PART_START = 0x1209
PKMN_C_SECONDARY_PART_END = 0x1D82
PKMN_C_JP_SECONDARY_PART_END = 0x7D3A
PKMN_C_JP_SECONDARY_PART_END = 0x7D3A

PKMN_C_PART_LENGTH = 0xB79
PKMN_C_JP_PART_LENGTH = 0xB31


PKMN_C_CHECKSUM_1 = 0x2D0D
PKMN_C_CHECKSUM_2 = 0x1F0D
PKMN_C_JP_CHECKSUM_2 = 0x7F0D

PKMN_C_PLAYER_GENDER_MALE = 0x0
PKMN_C_PLAYER_GENDER_FEMALE = 0x1

PKMN_JP_CHAR_TABLE = [ #Fill rest of this, 'f' is placeholder
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
  '', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'ア', 'イ',
  'ウ', 'エ', 'オ', 'カ', 'キ',
  'ク', 'ケ', 'コ', 'サ', 'シ',
  'ス', 'セ', 'ソ', 'タ', 'チ',
  'ツ', 'テ', 'ト', 'ナ', 'ニ',
  'ヌ', 'ネ', 'ノ', 'ハ', 'ヒ',
  'フ', 'ホ', 'マ', 'ミ', 'ム',
  'メ', 'モ', 'ヤ', 'ユ', 'ヨ',
  'ラ', 'ル', 'レ', 'ロ', 'ワ',
  'ヲ', 'ン', 'ッ', 'ャ', 'ュ',
  'ョ', 'ィ', 'あ', 'い', 'う',
  'え', 'お', 'か', 'き', 'く',
  'け', 'き', 'さ', 'し', 'す',
  'せ', 'そ', 'た', 'ち', 'つ',
  'て', 'と', 'な', 'に', 'ぬ',
  'ね', 'の', 'は', 'ひ', 'ふ',
  'へ', 'ほ', 'ま', 'み', 'む',
  'め', 'も', 'や', 'ゆ', 'よ',
  'ら', 'り', 'る', 'れ', 'ろ',
  'わ', 'を', 'ん', 'っ', 'ゃ',
  'ゅ', 'ょ', 'ー', 'f', 'f'
  '?', '!', '。', 'ァ', 'ゥ',
  'ェ', 'f', 'f', 'f', 'f',
  '円', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f', 'f', 'f', 'f', 'f',
  'f']

def print_checksums(data):
    sum = (data[PKMN_C_CHECKSUM_1] << 8) | data[PKMN_C_CHECKSUM_1+1]
    print(hex(sum))
    sum = (data[PKMN_C_CHECKSUM_2] << 8) | data[PKMN_C_CHECKSUM_2+1]
    #sum = (data[PKMN_C_JP_CHECKSUM_1] << 8) | data[PKMN_C_JP_CHECKSUM_1+1]
    print(hex(sum))

def write_checksums(data):
    sum = 0
    for i in range(PKMN_C_PRIMARY_PART_START, PKMN_C_PRIMARY_PART_START+PKMN_C_PART_LENGTH):
        sum += data[i]
    data[PKMN_C_CHECKSUM_1] = sum & 0xFF
    data[PKMN_C_CHECKSUM_1 + 1 ] = sum >> 8

    sum = 0
    for i in range(PKMN_C_SECONDARY_PART_START, PKMN_C_SECONDARY_PART_START+PKMN_C_PART_LENGTH):
        sum += data[i]
    data[PKMN_C_CHECKSUM_2] = sum & 0xFF
    data[PKMN_C_CHECKSUM_2 + 1] = sum >> 8


def copy_data(data):
    for i in range(0, PKMN_C_PART_LENGTH):
        data[PKMN_C_SECONDARY_PART_START+i] = data[PKMN_C_PRIMARY_PART_START+i]

def save_data_to_file(path, data):
    copy_data(data)
    write_checksums(data)
    with open(path, 'wb') as f:
        f.write(data)

def print_jp_char(char):
    print(PKMN_JP_CHAR_TABLE[char], end = "")

def foo(path, data):
    first_pokemon = PKMN_C_TEAM_POKEMON_LIST+8
    attack_offset = first_pokemon + 0x26 # These are 2 byte values
    max_hp_offset = first_pokemon + 0x24
    data[max_hp_offset] = 00 #nice
    data[max_hp_offset+1] = 69 #nice
    data[PKMN_C_GENDER] = PKMN_C_PLAYER_GENDER_MALE
    save_data_to_file(path, data)

def main():
    if len(sys.argv) > 1:
        path = sys.argv[1]
        with open(path, 'rb') as f:
            buf = bytearray(f.read())

        for i in range(PKMN_GSC_TRAINER_NAME, PKMN_GSC_MOM_NAME):
            if buf[i] != 0x50:
                print_jp_char(buf[i])
            else:
                print()
                break

        print_checksums(buf)
        foo(path, buf)
        print_checksums(buf)

if __name__ == "__main__":
    main()
