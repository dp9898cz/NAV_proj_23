# ESP32 - Měření vzdálenosti ultrazvukovým senzorem

## Projekt do předmětu [NAV](https://www.fit.vut.cz/study/course/NAV/.cs), VUT FIT 2023

autor: Daniel Pátek (xpatek08@stud.fit.vutbr.cz)

### Úvod

Cílem projektu je navrhnout a realizovat vestavěný systém pro měření vzdálenosti pomocí ultrazvukového senzoru. Součástí řešení je správné zapojení obvodu a naprogramování mikrokontroleru `Wemos D1 R32 UNO` s čipem `ESP32`. Naměřená vzdálenost bude zobrazena na OLED displej a rotační enkodér bude použit k ovládání četnosti měření, tedy ke kontrole prodlení mezi jednotlivými měčeními.

### Princip