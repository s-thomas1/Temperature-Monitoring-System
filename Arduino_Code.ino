#include <math.h>

// Power modes
#define POWER_DOWN  0
#define IDLE        1
#define ACTIVE      2

const int B = 4275000;             // B value of the thermistor
const int R0 = 100000;             // R0 = 100k
const int pinTempSensor = A0;      // Grove - Temperature Sensor connect to A0

const int sampleRate = 1;          // 1 sample per second
const int testLength = 60;         // 1 minute cycle
const int sampleCount = testLength * sampleRate;
float temperatureData[sampleCount];
float frequency[sampleCount];
float magnitude[sampleCount];

int previousMode = -1;

void setup() {
    Serial.begin(9600);
}

void collect_temperature_data() {
    for (int i = 0; i < sampleCount; i++) {
        int a = analogRead(pinTempSensor);

        float R = 1023.0 / a - 1.0;
        R = R0 * R;

        float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;
        temperatureData[i] = temperature;

        delay(1000); // 1 second interval
    }
}

void apply_dft() {
    for (int k = 0; k < sampleCount; k++) {
        float real = 0.0;
        float imaginary = 0.0;

        for (int n = 0; n < sampleCount; n++) {
            float angle = 2 * PI * k * n / sampleCount;
            real += temperatureData[n] * cos(angle);
            imaginary -= temperatureData[n] * sin(angle);
        }

        magnitude[k] = sqrt(real * real + imaginary * imaginary);
        frequency[k] = (float)k * sampleRate / sampleCount;
    }
}

int decide_power_mode() {
    float totalWeightedFrequency = 0.0;
    float totalMagnitude = 0.0;

    for (int i = 0; i < sampleCount; i++) {
        totalWeightedFrequency += frequency[i] * magnitude[i];
        totalMagnitude += magnitude[i];
    }

    float averageFrequency = (totalMagnitude > 0) ? totalWeightedFrequency / totalMagnitude : 0.0;

    if (averageFrequency > 0.5) {
        return ACTIVE;
    } else if (averageFrequency > 0.1) {
        return IDLE;
    } else {
        return POWER_DOWN;
    }
}

void print_summary(int mode) {
    float sumTemp = 0.0;
    for (int i = 0; i < sampleCount; i++) {
        sumTemp += temperatureData[i];
    }
    float avgTemp = sumTemp / sampleCount;

    float peakMagnitude = 0.0;
    float dominantFrequency = 0.0;
    for (int i = 0; i < sampleCount; i++) {
        if (magnitude[i] > peakMagnitude) {
            peakMagnitude = magnitude[i];
            dominantFrequency = frequency[i];
        }
    }

    Serial.print("Cycle Summary: Avg Temp = ");
    Serial.print(avgTemp, 2);
    Serial.print(" C, Dominant Freq = ");
    Serial.print(dominantFrequency, 2);
    Serial.print(" Hz, Mode = ");

    switch (mode) {
        case ACTIVE:
            Serial.println("Active");
            break;
        case IDLE:
            Serial.println("Idle");
            break;
        case POWER_DOWN:
            Serial.println("Power-down");
            break;
    }
}

void loop() {
    collect_temperature_data();
    apply_dft();

    int currentMode = decide_power_mode();

    if (currentMode != previousMode) {
        previousMode = currentMode;
    }

    print_summary(currentMode);

    // One cycle per minute, sleep until next loop
    delay(1000);  // already waited 60 seconds in collection
}
