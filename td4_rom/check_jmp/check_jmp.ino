unsigned char rom[] = {
  // JMP命令のチェック
  B00110000, //MOV A, 0000
  B00000001, //ADD A, 0001
  B00000001, //ADD A, 0001
  B00000001, //ADD A, 0001
  B01110000, //MOV B, 0000
  B01010001, //ADD B, 0001
  B01010001, //ADD B, 0001
  B01010001, //ADD B, 0001
  B11110000, //JMP 0000
};

void setup() {
  Serial.begin(9600);
  DDRB = DDRB | B00001111;
  DDRC = DDRC | B00001111;
}

void loop() {
  // アドレス入力 D5 D4 D3 D2 番ピン（右が最下位ビット）
  // データ出力   D11 D10 D9 D8 A3 A2 A1 A0 番ピン（右が最下位ビット）
  unsigned char addr = (PIND & B00111100)>>2;
  Serial.println(addr);

  PORTC = (PORTC & B11110000) | (rom[addr] & B00001111);
  PORTB = (PORTB & B11110000) | ((rom[addr] & B11110000)>>4);
}
