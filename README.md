# Alarme Antifurto com Arduino

Projeto de alarme antifurto feito com Arduino Uno e sensor de movimento PIR. Quando o sensor detecta movimento, um LED vermelho acende e o horário do evento é registrado. Sem movimento, o LED verde fica aceso. Um botão liga e desliga o sensor.

## Funcionalidades

- Detecção de movimento com sensor PIR HC-SR501
- LED vermelho acende quando há movimento
- LED verde acende quando não há movimento (ou quando o sensor está desligado)
- Botão para ligar e desligar o sensor
- Registro do horário de cada movimento no Monitor Serial
- Contador de disparos, com o total exibido ao desligar o sensor

## Materiais

| Quantidade | Item |
|---|---|
| 1 | Arduino Uno R3 e cabo USB |
| 1 | Sensor de movimento PIR HC-SR501 |
| 1 | Protoboard de 400 pontos |
| 1 | LED vermelho |
| 1 | LED verde |
| 2 | Resistores de 220 Ω |
| 1 | Botão (pushbutton) |
| vários | Jumpers macho/macho |

## Ligações

| Componente | Conexão no Arduino |
|---|---|
| Sensor PIR: VCC | 5V |
| Sensor PIR: GND | GND |
| Sensor PIR: OUT | Pino 2 |
| Botão (um lado) | Pino 4 |
| Botão (outro lado) | GND |
| LED vermelho (+), com resistor de 220 Ω | Pino 9 |
| LED verde (+), com resistor de 220 Ω | Pino 10 |
| LEDs (-) | GND |

O botão usa o resistor interno do Arduino (`INPUT_PULLUP`), então não precisa de resistor externo.

## Como usar

1. Monte o circuito conforme a tabela de ligações.
2. Abra o arquivo `.ino` na Arduino IDE.
3. Em Ferramentas, selecione a placa Arduino Uno e a porta USB correta.
4. Clique em Upload.
5. Abra o Monitor Serial (9600 baud) para ver os registros.
6. Espere cerca de 30 a 60 segundos para o sensor PIR se estabilizar.
7. Passe a mão de lado na frente da cúpula branca do sensor:
   - LED vermelho acende e aparece no monitor `[hh:mm:ss] MOVIMENTO DETECTADO - disparo numero N`
   - Sem movimento, o LED verde volta a acender
8. Aperte o botão para desligar o sensor (só o LED verde fica aceso). Aperte de novo para religar.

## Observações sobre o horário

O Arduino Uno não tem relógio interno. O horário é calculado a partir da hora em que o código foi compilado e enviado (`__TIME__`), e por isso:

- A hora pode ficar alguns segundos atrasada. Ajuste o valor de `ATRASO_UPLOAD` no código se necessário.
- Ao reiniciar o Arduino (ou abrir o Monitor Serial), o relógio e o contador de disparos voltam ao início.

