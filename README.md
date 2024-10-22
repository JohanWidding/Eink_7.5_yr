# E-ink 7.5" - ESP32-oppsett

Denne veiledningen hjelper deg med å sette opp en ESP32 for å bruke en 7,5-tommers E-ink-skjerm. Følg stegene nøye for å sikre riktig installasjon og konfigurasjon av nødvendig programvare.

## Trinn 1: Last ned og installer Arduino IDE

1. Gå til [Arduino sine nettsider](https://www.arduino.cc/en/software) for å laste ned den nyeste versjonen av Arduino IDE.
2. Installer programmet på din datamaskin i henhold til standard installasjonsrutiner for ditt operativsystem.

## Trinn 2: Konfigurer ESP32-støtte i Arduino IDE

1. Åpne Arduino IDE.
2. Gå til **Fil** > **Innstillinger** (*Preferences*).
3. I feltet for **Additional Boards Manager URLs** lim inn følgende URL:
https://dl.espressif.com/dl/package_esp32_index.json

4. Klikk **OK**.

## Trinn 3: Installer ESP32-pakken

1. Gå til **Verktøy** > **Kort** > **Kortbehandling** (*Tools* > *Board* > *Boards Manager*).
2. Søk etter `esp32`.
3. Velg **ESP32 by Espressif Systems** og klikk **Installer**.

## Trinn 4: Velg ESP32-kort

1. Gå til **Verktøy** > **Kort** (*Tools* > *Board*) og velg **ESP32 Dev Module**.

## Trinn 5: Installer nødvendige biblioteker

Installer følgende biblioteker for å kunne bruke E-ink-skjermen:
1. GxEPD2
2. Adafruit GFX Library

Disse bibliotekene kan installeres via **Bibliotekbehandling** (*Library Manager*) i Arduino IDE.

## Trinn 6: Konfigurer prosjektfilene

Plasser prosjektfilene i riktig mappe i Arduino-mappen din.

Nå er du klar til å laste opp koden til ESP32 og begynne å bruke E-ink-skjermen.
