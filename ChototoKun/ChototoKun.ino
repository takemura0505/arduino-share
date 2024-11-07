struct shift_reg {
  int ser_pin;
  int rclk_pin;
  int srclk_pin;
};

static struct shift_reg shift_regs[4] = {
  {
    .ser_pin = 2,
    .rclk_pin = 3,
    .srclk_pin = 4,
  },
  {
    .ser_pin = 5,
    .rclk_pin = 6,
    .srclk_pin = 7,
  },
  {
    .ser_pin = 8,
    .rclk_pin = 9,
    .srclk_pin = 10,
  },
  {
    .ser_pin = 11,
    .rclk_pin = 12,
    .srclk_pin = 13,
  },
};

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
}

void pulse(int pin) {
  digitalWrite(pin, true);
  delay(1);
  digitalWrite(pin, false);
}

void write_shift_register(int ser, int rclk, int srclk, uint8_t a) {
  digitalWrite(rclk, false);
  for (int i = 0; i < 8; ++i) {
    digitalWrite(srclk, false);
    digitalWrite(ser, a >> i & 1);
    digitalWrite(srclk, true);
  }
  digitalWrite(rclk, true);
}

void loop() {
  int pins[4][3] = {
    { 2, 3, 4 },
    { 5, 6, 7 },
    { 8, 9, 10 },
    { 11, 12, 13 },
  };
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 8; ++j) {
      write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0x80 >> j);
      delay(10);
      if (!digitalRead(A0)) {
        delay(500);
        if (j != 7) {
        for (int i = 0; i < 4; ++i)
          write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0x01);
        delay(500);
        for (int i = 0; i < 4; ++i)
          write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0x00);
        delay(500);
        for (int i = 0; i < 4; ++i)
          write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0x01);
        delay(500);
        for (int i = 0; i < 4; ++i)
          write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0x00);
        delay(500);
        for (int i = 0; i < 4; ++i)
          write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0x01);
        delay(500);
        for (int i = 0; i < 4; ++i)
          write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0x00);
        delay(500);
        } else {
        for (int n = 0; n < 4; ++n) {
        for (int i = 0; i < 4; ++i) {
          for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < 4; ++k)
              write_shift_register(pins[k][0], pins[k][1], pins[k][2], 0);
            write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0x80 >> j);
            write_shift_register(pins[3 - i][0], pins[3 - i][1], pins[3 - i][2], 0x01 << j);
            delay(10);
          }
        }
        }
        for (int k = 0; k < 4; ++k)
          write_shift_register(pins[k][0], pins[k][1], pins[k][2], 0);
        }
        delay(500);
      }
    }
    write_shift_register(pins[i][0], pins[i][1], pins[i][2], 0);
  }
}
