struct TableLamp: Service::LightBulb {
  private:
    void setLampState(bool state) {
      if (state) {
        digitalWrite(lampPinA, LOW);
        digitalWrite(lampPinB, HIGH);
        digitalWrite(lampPinC, HIGH);
      } else {
        digitalWrite(lampPinA, LOW);
        digitalWrite(lampPinB, LOW);
        digitalWrite(lampPinC, LOW);
      }
    }

  public:
    int lampPinA;
    int lampPinB;
    int lampPinC;
    int buttonPin;

    SpanCharacteristic *power;

    TableLamp(int pinA, int pinB, int pinC, int button) : Service::LightBulb() {
      power = new Characteristic::On(false, true);

      pinMode(pinA, OUTPUT);
      pinMode(pinB, OUTPUT);
      pinMode(pinC, OUTPUT);

      lampPinA = pinA;
      lampPinB = pinB;
      lampPinC = pinC;
      buttonPin = button;

      new SpanButton(button, SpanButton::TRIGGER_ON_HIGH);
      setLampState(power->getVal());
    }

    void button(int pin, int pressType) override {
      bool state = !power->getVal();
      setLampState(state);
      power->setVal(state);
    }

    boolean update() {
      setLampState(power->getNewVal());
      return true;
    }
};
