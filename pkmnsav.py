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
PKMN_C_JP_TEAM_POKEMON_LIST = 0x281A
PKMN_C_POKEDEX_OWNED = 0x2A27
PKMN_C_POKEDEX_SEEN = 0x2A47

PKMN_C_JP_PRIMARY_PART_START = 0x2009
PKMN_C_JP_PRIMARY_PART_END = 0x2B3A
PKMN_C_JP_SECONDARY_PART_START = 0x7209
PKMN_C_JP_SECONDARY_PART_END = 0x7D3A

PKMN_C_JP_CHECKSUM_1 = 0x2D0D
PKMN_C_JP_CHECKSUM_2 = 0x7F0D

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

def print_checksum(data):
    sum = (data[PKMN_C_JP_CHECKSUM_1] << 8) | data[PKMN_C_JP_CHECKSUM_1+1]
    print(hex(sum))

def write_checksum(data):
    sum = 0
    for i in range(PKMN_C_JP_PRIMARY_PART_START, PKMN_C_JP_PRIMARY_PART_END+1):
        sum += data[i]
    data[PKMN_C_JP_CHECKSUM_1] = sum >> 8
    data[PKMN_C_JP_CHECKSUM_1+1] = sum & 0xFF

    sum = 0
    for i in range(PKMN_C_JP_SECONDARY_PART_START, PKMN_C_JP_SECONDARY_PART_END+1):
        sum += data[i]
    data[PKMN_C_JP_CHECKSUM_2] = sum >> 8
    data[PKMN_C_JP_CHECKSUM_2+1] = sum & 0xFF

def save_data_to_file(path, data):
    write_checksum(data)
    with open(path, 'wb') as f:
        f.write(data)

def print_jp_char(char):
    print(PKMN_JP_CHAR_TABLE[char])

def foo(path, data):
    save_data_to_file(path, data)

def main():
    path = sys.argv[1]
    with open(path, 'rb') as f:
        buf = bytearray(f.read())
    for i in range(PKMN_GSC_TRAINER_NAME, PKMN_GSC_MOM_NAME):
        print_jp_char(buf[i])
    print_checksum(buf)
    #foo()

if __name__ == "__main__":
    main()
