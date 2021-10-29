unsigned char rom[] = {
  // JNC命令の確認
  B00111111, // MOV A, 1111
  B11100000, // JNC(C=1): ジャンプしないことを確認
  B00111010, // MOV A, 1010: Aレジスタが1010になり、キャリーはゼロに
  B11100000, // JNC(C=0)
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
