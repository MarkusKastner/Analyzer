/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "HexFormatter.h"

#include <sstream>
#include <iomanip>

namespace analyzer {
  namespace interpreter {

    HexFormatter::HexFormatter()
      :Formatter(), space(L"  "), exp(), hex()
    {
    }

    HexFormatter::HexFormatter(const std::shared_ptr<std::vector<unsigned char>>& data)
      :Formatter(data)
    {
    }

    HexFormatter::~HexFormatter()
    {

    }

    std::shared_ptr<std::wstring> HexFormatter::GetText()
    {
      auto& data = (*this->getData());
      std::shared_ptr<std::wstring> text(new std::wstring());

      if (data.size() == 0) {
        return text;
      }
      int byteCounter = 0;

      for (auto& byte : data) {
        this->hex += this->char2Hex(byte);
        this->hex += this->space;

        this->exp += L"[";
        this->exp += this->char2Expression(byte);
        this->exp += L"]";
        byteCounter++;

        if (byteCounter >= 8) {
          this->append(text);
          byteCounter = 0;
        }
      }
      if (byteCounter != 0) {
        this->append(text);
      }
      
      if (text->at(text->size() - 1) == '\n') {
        text->pop_back();
      }
      return text;
    }

    void HexFormatter::append(const std::shared_ptr<std::wstring> & text)
    {
      text->append(this->hex);
      text->append(L"\t");
      text->append(this->exp);
      text->append(L"\n");

      this->hex.clear();
      this->exp.clear();
    }

    std::wstring HexFormatter::char2Hex(const unsigned char & value)
    {
      std::wstringstream stream;
      stream << std::hex << value;
      return stream.str();
    }

    std::wstring HexFormatter::char2Expression(const unsigned char & value)
    {
      std::wstring exp;
      switch (value) {
      case 0:	exp = L"NUL"; break;
      case 1:	exp = L"SOH"; break;
      case 2:	exp = L"STX"; break;
      case 3:	exp = L"ETX"; break;
      case 4:	exp = L"EOT"; break;
      case 5:	exp = L"ENQ"; break;
      case 6:	exp = L"ACK"; break;
      case 7:	exp = L"BEL"; break;
      case 8:	exp = L"BS"; break;
      case 9:	exp = L"HT"; break;
      case 10: exp = L"LF"; break;
      case 11: exp = L"VT"; break;
      case 12: exp = L"FF"; break;
      case 13: exp = L"CR"; break;
      case 14: exp = L"SO"; break;
      case 15: exp = L"SI"; break;
      case 16: exp = L"DLE"; break;
      case 17: exp = L"DC1"; break;
      case 18: exp = L"DC2"; break;
      case 19: exp = L"DC3"; break;
      case 20: exp = L"DC4"; break;
      case 21: exp = L"NAK"; break;
      case 22: exp = L"SYN"; break;
      case 23: exp = L"ETB"; break;
      case 24: exp = L"CAN"; break;
      case 25: exp = L"EM"; break;
      case 26: exp = L"SUB"; break;
      case 27: exp = L"ESC"; break;
      case 28: exp = L"FS"; break;
      case 29: exp = L"GS"; break;
      case 30: exp = L"RS"; break;
      case 31: exp = L"US"; break;
      case 32: exp = L"SPACE"; break;
      case 33: exp = L"!"; break;
      case 34: exp = L"\""; break;
      case 35: exp = L"#"; break;
      case 36: exp = L"$"; break;
      case 37: exp = L"%"; break;
      case 38: exp = L"&"; break;
      case 39: exp = L"'"; break;
      case 40: exp = L"("; break;
      case 41: exp = L")"; break;
      case 42: exp = L"*"; break;
      case 43: exp = L"+"; break;
      case 44: exp = L","; break;
      case 45: exp = L"-"; break;
      case 46: exp = L"."; break;
      case 47: exp = L"/"; break;
      case 48: exp = L"0"; break;
      case 49: exp = L"1"; break;
      case 50: exp = L"2"; break;
      case 51: exp = L"3"; break;
      case 52: exp = L"4"; break;
      case 53: exp = L"5"; break;
      case 54: exp = L"6"; break;
      case 55: exp = L"7"; break;
      case 56: exp = L"8"; break;
      case 57: exp = L"9"; break;
      case 58: exp = L":"; break;
      case 59: exp = L";"; break;
      case 60: exp = L"<"; break;
      case 61: exp = L"="; break;
      case 62: exp = L">"; break;
      case 63: exp = L"?"; break;
      case 64: exp = L"@"; break;
      case 65: exp = L"A"; break;
      case 66: exp = L"B"; break;
      case 67: exp = L"C"; break;
      case 68: exp = L"D"; break;
      case 69: exp = L"E"; break;
      case 70: exp = L"F"; break;
      case 71: exp = L"G"; break;
      case 72: exp = L"H"; break;
      case 73: exp = L"I"; break;
      case 74: exp = L"J"; break;
      case 75: exp = L"K"; break;
      case 76: exp = L"L"; break;
      case 77: exp = L"M"; break;
      case 78: exp = L"N"; break;
      case 79: exp = L"O"; break;
      case 80: exp = L"P"; break;
      case 81: exp = L"Q"; break;
      case 82: exp = L"R"; break;
      case 83: exp = L"S"; break;
      case 84: exp = L"T"; break;
      case 85: exp = L"U"; break;
      case 86: exp = L"V"; break;
      case 87: exp = L"W"; break;
      case 88: exp = L"X"; break;
      case 89: exp = L"Y"; break;
      case 90: exp = L"Z"; break;
      case 91: exp = L"["; break;
      case 92: exp = L"\\"; break;
      case 93: exp = L"]"; break;
      case 94: exp = L"^"; break;
      case 95: exp = L"_"; break;
      case 96: exp = L"`"; break;
      case 97: exp = L"a"; break;
      case 98: exp = L"b"; break;
      case 99: exp = L"c"; break;
      case 100:	exp = L"d"; break;
      case 101:	exp = L"e"; break;
      case 102:	exp = L"f"; break;
      case 103:	exp = L"g"; break;
      case 104:	exp = L"h"; break;
      case 105:	exp = L"i"; break;
      case 106:	exp = L"j"; break;
      case 107:	exp = L"k"; break;
      case 108:	exp = L"l"; break;
      case 109:	exp = L"m"; break;
      case 110:	exp = L"n"; break;
      case 111:	exp = L"o"; break;
      case 112:	exp = L"p"; break;
      case 113:	exp = L"q"; break;
      case 114:	exp = L"r"; break;
      case 115:	exp = L"s"; break;
      case 116:	exp = L"t"; break;
      case 117:	exp = L"u"; break;
      case 118:	exp = L"v"; break;
      case 119:	exp = L"w"; break;
      case 120:	exp = L"x"; break;
      case 121:	exp = L"y"; break;
      case 122:	exp = L"z"; break;
      case 123:	exp = L"{"; break;
      case 124:	exp = L"|"; break;
      case 125:	exp = L"}"; break;
      case 126:	exp = L"~"; break;
      case 127:	exp = L"DEL"; break;
      case 128:	exp = L"€"; break;
      case 129:	exp = L"EMPTY"; break;
      case 130:	exp = L"‚"; break;
      case 131:	exp = L"ƒ"; break;
      case 132:	exp = L"„"; break;
      case 133:	exp = L"…"; break;
      case 134:	exp = L"†"; break;
      case 135:	exp = L"‡"; break;
      case 136:	exp = L"ˆ"; break;
      case 137:	exp = L"‰"; break;
      case 138:	exp = L"Š"; break;
      case 139:	exp = L"‹"; break;
      case 140:	exp = L"Œ"; break;
      case 141:	exp = L"EMPTY"; break;
      case 142:	exp = L"Ž"; break;
      case 143:	exp = L"EMPTY"; break;
      case 144:	exp = L"EMPTY"; break;
      case 145:	exp = L"‘"; break;
      case 146:	exp = L"’"; break;
      case 147:	exp = L"“"; break;
      case 148:	exp = L"”"; break;
      case 149:	exp = L"•"; break;
      case 150:	exp = L"–"; break;
      case 151:	exp = L"—"; break;
      case 152:	exp = L"˜"; break;
      case 153:	exp = L"™"; break;
      case 154:	exp = L"š"; break;
      case 155:	exp = L"›"; break;
      case 156:	exp = L"œ"; break;
      case 157:	exp = L"EMPTY"; break;
      case 158:	exp = L"ž"; break;
      case 159:	exp = L"Ÿ"; break;
      case 160:	exp = L"NBSP"; break;
      case 161: exp = L"¡"; break;
      case 162: exp = L"¢"; break;
      case 163: exp = L"£"; break;
      case 164: exp = L"¤"; break;
      case 165: exp = L"¥"; break;
      case 166: exp = L"¦"; break;
      case 167: exp = L"§"; break;
      case 168: exp = L"¨"; break;
      case 169: exp = L"©"; break;
      case 170: exp = L"ª"; break;
      case 171: exp = L"«"; break;
      case 172: exp = L"¬"; break;
      case 173: exp = L"SHY"; break;
      case 174:	exp = L"®"; break;
      case 175:	exp = L"¯"; break;
      case 176:	exp = L"°"; break;
      case 177:	exp = L"±"; break;
      case 178:	exp = L"²"; break;
      case 179:	exp = L"³"; break;
      case 180:	exp = L"´"; break;
      case 181:	exp = L"µ"; break;
      case 182:	exp = L"¶"; break;
      case 183:	exp = L"·"; break;
      case 184:	exp = L"¸"; break;
      case 185:	exp = L"¹"; break;
      case 186:	exp = L"º"; break;
      case 187:	exp = L"»"; break;
      case 188:	exp = L"¼"; break;
      case 189:	exp = L"½"; break;
      case 190:	exp = L"¾"; break;
      case 191:	exp = L"¿"; break;
      case 192:	exp = L"À"; break;
      case 193:	exp = L"Á"; break;
      case 194:	exp = L"Â"; break;
      case 195:	exp = L"Ã"; break;
      case 196:	exp = L"Ä"; break;
      case 197:	exp = L"Å"; break;
      case 198:	exp = L"Æ"; break;
      case 199:	exp = L"Ç"; break;
      case 200:	exp = L"È"; break;
      case 201:	exp = L"É"; break;
      case 202:	exp = L"Ê"; break;
      case 203:	exp = L"Ë"; break;
      case 204:	exp = L"Ì"; break;
      case 205:	exp = L"Í"; break;
      case 206:	exp = L"Î"; break;
      case 207:	exp = L"Ï"; break;
      case 208:	exp = L"Ð"; break;
      case 209:	exp = L"Ñ"; break;
      case 210:	exp = L"Ò"; break;
      case 211:	exp = L"Ó"; break;
      case 212:	exp = L"Ô"; break;
      case 213:	exp = L"Õ"; break;
      case 214:	exp = L"Ö"; break;
      case 215:	exp = L"×"; break;
      case 216:	exp = L"Ø"; break;
      case 217:	exp = L"Ù"; break;
      case 218:	exp = L"Ú"; break;
      case 219:	exp = L"Û"; break;
      case 220:	exp = L"Ü"; break;
      case 221:	exp = L"Ý"; break;
      case 222:	exp = L"Þ"; break;
      case 223:	exp = L"ß"; break;
      case 224:	exp = L"à"; break;
      case 225:	exp = L"á"; break;
      case 226:	exp = L"â"; break;
      case 227:	exp = L"ã"; break;
      case 228:	exp = L"ä"; break;
      case 229:	exp = L"å"; break;
      case 230:	exp = L"æ"; break;
      case 231:	exp = L"ç"; break;
      case 232:	exp = L"è"; break;
      case 233:	exp = L"é"; break;
      case 234:	exp = L"ê"; break;
      case 235:	exp = L"ë"; break;
      case 236:	exp = L"ì"; break;
      case 237:	exp = L"í"; break;
      case 238:	exp = L"î"; break;
      case 239:	exp = L"ï"; break;
      case 240:	exp = L"ð"; break;
      case 241:	exp = L"ñ"; break;
      case 242:	exp = L"ò"; break;
      case 243:	exp = L"ó"; break;
      case 244:	exp = L"ô"; break;
      case 245:	exp = L"õ"; break;
      case 246:	exp = L"ö"; break;
      case 247:	exp = L"÷"; break;
      case 248:	exp = L"ø"; break;
      case 249:	exp = L"ù"; break;
      case 250:	exp = L"ú"; break;
      case 251:	exp = L"û"; break;
      case 252:	exp = L"ü"; break;
      case 253:	exp = L"ý"; break;
      case 254:	exp = L"þ"; break;
      case 255:	exp = L"ÿ"; break;
      default: exp = L"[EMPTY]";
      }
      return exp;
    }
  }
}